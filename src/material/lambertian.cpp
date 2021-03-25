#include "lambertian.h"
#include "../core/onb.h"
#include "../core/pdf.h"

namespace mypt {

bool Lambertian::scatter(
    const Ray& /* r_in */, SurfaceInteraction& si
) const {
    si.is_specular = false;
    si.attenuation = albedo->value(si.uv, si.p);
    si.pdf_ptr = std::make_shared<CosinePDF>(si.n);
    return true;
}

Float Lambertian::scattering_pdf(
    const Ray& /* r_in */, const SurfaceInteraction& si
) const {
    auto cosine = dot(si.n, normalize(si.scattered.direction()));
    return cosine < 0 ? 0 : cosine/pi;
}

}