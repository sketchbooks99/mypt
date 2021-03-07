#include "dielectric.h"
#include "../core/fresnel.h"

namespace mypt {

bool Dielectric::scatter(
    const Ray& r_in, SurfaceInteraction& si
) const {
    auto wi = normalize(r_in.direction());

    si.is_specular = true;
    si.pdf_ptr = 0;
    si.attenuation = albedo;

    Float ni = 1.0; // Air
    Float nt = ior; // Material specific IOR
    Float cosine = dot(wi, si.n);
    bool into = cosine < 0;
    auto outward_normal = into ? si.n : -si.n;

    // swap ni and nt due to the order of mediums.
    if (!into) std::swap(ni, nt);

    cosine = fabs(cosine);
    Float sine = sqrt(1.0 - cosine*cosine);
    bool cannot_refract = (ni / nt) * sine > 1.0;

    Float reflect_prob = fresnel_dielectric(cosine, nt / ni);
    if (cannot_refract || reflect_prob > random_float())
        si.scattered = Ray(si.p, reflect(wi, outward_normal));
    else
        si.scattered = Ray(si.p, refract(wi, outward_normal, cosine, ni, nt));
    return true;
}


}