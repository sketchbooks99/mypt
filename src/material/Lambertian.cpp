#include "Lambertian.h"

bool Lambertian::scatter(
    const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
) const {
    vec3 scatter_direction = normalize(rec.normal + random_unit_vector());
    scattered = Ray(rec.p, scatter_direction, r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
}