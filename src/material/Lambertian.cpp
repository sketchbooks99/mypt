#include "Lambertian.h"

bool Lambertian::scatter(
    const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered, double& pdf
) const {
    vec3 scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.is_near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, normalize(scatter_direction), r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    pdf = dot(rec.normal, scattered.direction()) / pi;
    return true;
}

double Lambertian::scattering_pdf(
    const Ray& r_in, const HitRecord& rec, const Ray& scattered
) const {
    auto cosine = dot(rec.normal, normalize(scattered.direction()));
    return cosine < 0 ? 0 : cosine/pi;
}