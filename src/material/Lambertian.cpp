#include "Lambertian.h"
#include "../core/ONB.h"

namespace mypt {

bool Lambertian::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const {
    srec.is_specular = false;
    srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
    srec.pdf = std::make_shared<CosinePDF>(rec.normal);
    rec.p += rec.normal * eps;
    return true;
}

double Lambertian::scattering_pdf(
    const Ray& r_in, const HitRecord& rec, const Ray& scattered
) const {
    auto cosine = dot(rec.normal, normalize(scattered.direction()));
    return cosine < 0 ? 0 : cosine/pi;
}

}