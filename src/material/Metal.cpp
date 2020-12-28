#include "Metal.h"
#include "../core/bsdf.h"

namespace mypt {

bool Metal::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const {
    vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
    srec.specular_ray = Ray(rec.p, reflected+fuzz*random_in_unit_sphere(), r_in.time());
    srec.attenuation = albedo;
    srec.is_specular = true;
    srec.pdf = 0;

    return true;
}

}