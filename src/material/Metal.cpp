#include "Metal.h"

bool Metal::scatter(
    const Ray& r_in, HitRecord& rec, vec3& attenuation, Ray& scattered, double& pdf
) const {
    vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}