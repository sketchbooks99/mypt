#include "Metal.h"

namespace mypt {

bool Metal::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const {
    vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
    srec.specular_ray = Ray(normalize(r_in.direction()), rec.normal);
    srec.attenuation = albedo;
    srec.is_specular = true;
    srec.pdf = 0;
    return true;
}

}