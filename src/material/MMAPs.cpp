#include "MMAPs.h"

namespace mypt {

bool MMAPs::scatter(
    const Ray& r_in, HitRecord& rec, vec3& attenuation, Ray& scattered, double& pdf
) const {
    vec3 retro_transmitted = retro_transmit(normalize(r_in.direction()), rec.normal);
    rec.p += dot(retro_transmitted, rec.normal) < 0 ? -rec.normal * eps : rec.normal * eps;
    scattered = Ray(rec.p, retro_transmitted + fuzz*random_in_unit_sphere());
    attenuation = albedo * 0.5f;
    return true;
}

}