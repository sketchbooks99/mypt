#include "normal.h"
#include "../core/pdf.h"

namespace mypt {

bool NormalMat::scatter(
    const Ray& /* r_in */, SurfaceInteraction& si
) const {
    si.is_specular = false;
    si.attenuation = normalize(si.n);
    si.pdf_ptr = std::make_shared<CosinePDF>(si.n);
    si.p += si.n * eps;
    return true;
}

Float NormalMat::scattering_pdf(
    const Ray& /* r_in */, const SurfaceInteraction& si
) const {
    auto cosine = dot(si.n, normalize(si.scattered.direction()));
    return cosine < 0 ? 0 : cosine / pi;
}

}