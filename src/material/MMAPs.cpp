#include "MMAPs.h"

namespace mypt {

bool MMAPs::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) {
    vec3 retro_transmitted = retro_transmit(normalize(r_in.direction()), rec.normal);
    rec.p += dot(retro_transmitted, rec.normal) < 0 ? -rec.normal * eps : rec.normal * eps;
    srec.scattered = Ray(rec.p, retro_transmitted + fuzz*random_in_unit_sphere());
    srec.attenuation = albedo * 0.5f;
    srec.pdf = nullptr;
    srec.is_specular = true;
    return true;
}

}