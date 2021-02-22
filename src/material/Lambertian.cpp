#include "Lambertian.h"
#include "../core/ONB.h"
#include "../core/PDF.h"

namespace mypt {

bool Lambertian::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) {
    srec.is_specular = false;
    srec.attenuation = albedo->value(rec.uv.x, rec.uv.y, rec.p);
    rec.set_face_normal(r_in, rec.normal);
    srec.pdf = std::make_shared<CosinePDF>(rec.normal);
    return true;
}

Float Lambertian::scattering_pdf(
    const Ray& /* r_in */, const HitRecord& rec, const Ray& scattered
) {
    auto cosine = dot(rec.normal, normalize(scattered.direction()));
    return cosine < 0 ? 0 : cosine/pi;
}

}