#include "Lambertian.h"
#include "../core/ONB.h"

namespace mypt {

bool Lambertian::scatter(
    const Ray& r_in, HitRecord& rec, vec3& attenuation, Ray& scattered, double& pdf
) const {
    // vec3 scatter_direction = rec.normal + random_unit_vector();

    // // Catch degenerate scatter direction
    // if (scatter_direction.is_near_zero())
    //     scatter_direction = rec.normal;

    ONB onb;
    onb.build_from_w(rec.normal);
    auto direction = onb.local(random_cosine_direction());

    rec.p += rec.normal * 1e-8f;
    scattered = Ray(rec.p, normalize(direction), r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    pdf = dot(onb.w, scattered.direction()) / pi;
    return true;
}

double Lambertian::scattering_pdf(
    const Ray& r_in, const HitRecord& rec, const Ray& scattered
) const {
    auto cosine = dot(rec.normal, normalize(scattered.direction()));
    return cosine < 0 ? 0 : cosine/pi;
}

}