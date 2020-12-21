#include "Dielectric.h"

namespace mypt {

bool Dielectric::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const {
    srec.is_specular = true;
    srec.pdf = nullptr;
    srec.attenuation = albedo;
    double refraction_ratio = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

    vec3 unit_direction = normalize(r_in.direction());
    double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
    vec3 direction;
    // Decide out going direction stochastically with frenel approximation
    double reflect_prob = schlick(cos_theta, refraction_ratio);
    if(refraction_ratio * sin_theta > 1.0 || random_double() < reflect_prob) {
        direction = reflect(unit_direction, rec.normal);
    }
    else {
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    }
    srec.specular_ray = Ray(rec.p, direction, r_in.time());
    return true;
}

}