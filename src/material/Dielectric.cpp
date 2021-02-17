#include "Dielectric.h"
#include "../core/bsdf.h"

namespace mypt {

bool Dielectric::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const  {
    srec.is_specular = true;
    srec.pdf = 0;
    srec.attenuation = albedo;
    bool into = dot(r_in.direction(), rec.normal) < 0;
    float ni_over_nt = into ? 1.0 / ior : ior;
    auto outward_normal = into ? rec.normal : -rec.normal;
    
    float cosine = fmin(dot(-normalize(r_in.direction()), outward_normal), 1.0);
    float sine = sqrt(1.0 - cosine*cosine);

    bool cannot_refract = ni_over_nt * sine > 1.0;

    float reflect_prob = schlick(cosine, ior);
    if(cannot_refract || reflect_prob > random_float()) 
        srec.specular_ray = Ray(rec.p, reflect(r_in.direction(), outward_normal));
    else
        srec.specular_ray = Ray(rec.p, refract(r_in.direction(), outward_normal, ni_over_nt));
    return true;
}

}