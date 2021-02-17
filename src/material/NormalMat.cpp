#include "NormalMat.h"
#include "../core/PDF.h"

namespace mypt {

bool NormalMat::scatter(
    const Ray& /* r_in */, HitRecord& rec, ScatterRecord& srec
) const {
    srec.is_specular = false;
    srec.attenuation = normalize(rec.normal);
    srec.pdf = std::make_shared<CosinePDF>(rec.normal);
    rec.p += rec.normal * eps;
    return true;
}

Float NormalMat::scattering_pdf(
    const Ray& /* r_in */, const HitRecord& rec, const Ray& scattered
) const {
    auto cosine = dot(rec.normal, normalize(scattered.direction()));
    return cosine < 0 ? 0 : cosine / pi;
}

}