#include "dielectric.h"
#include "../core/bsdf.h"

namespace mypt {

bool Dielectric::scatter(
    const Ray& r_in, SurfaceInteraction& si
) const  {
    si.is_specular = true;
    si.pdf_ptr = 0;
    si.attenuation = albedo;
    bool into = dot(r_in.direction(), si.n) < 0;
    float ni_over_nt = into ? 1.0 / ior : ior;
    auto outward_normal = into ? si.n : -si.n;
    
    float cosine = fmin(dot(-normalize(r_in.direction()), outward_normal), 1.0);
    float sine = sqrt(1.0 - cosine*cosine);

    bool cannot_refract = ni_over_nt * sine > 1.0;

    float reflect_prob = schlick(cosine, ior);
    if(cannot_refract || reflect_prob > random_float()) 
        si.scattered = Ray(si.p, reflect(r_in.direction(), outward_normal));
    else
        si.scattered = Ray(si.p, refract(r_in.direction(), outward_normal, ni_over_nt));
    return true;
}


}