#include "NormalMat.h"
#include "../core/PDF.h"

namespace mypt {

bool NormalMat::scatter(
    const Ray& /* r_in */, HitRecord& rec, ScatterRecord& srec
) {
    srec.is_specular = false;
    srec.attenuation = normalize(rec.normal);
    srec.pdf = std::make_shared<CosinePDF>(rec.normal);
    rec.p += rec.normal * eps;
    return !is_emit;
}

double NormalMat::scattering_pdf(
    const Ray& /* r_in */, const HitRecord& rec, const Ray& scattered
) {
    auto cosine = dot(rec.normal, normalize(scattered.direction()));
    return cosine < 0 ? 0 : cosine / pi;
}

vec3 NormalMat::emitted( const Ray& /* r_in */, const HitRecord& rec ) {
    if (is_emit) return abs(rec.normal);
    else return vec3(0.0f);
}

}