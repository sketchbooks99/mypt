#include "metal.h"
#include "../core/fresnel.h"

namespace mypt {

bool Metal::scatter(
    const Ray& r_in, SurfaceInteraction& si
) const {
    auto wi = normalize(r_in.direction());

    auto reflected = reflect(wi, si.n);
    si.scattered = Ray(si.p, reflected+fuzz*random_in_unit_sphere(), r_in.time());
    si.attenuation = albedo;
    si.is_specular = true;
    si.pdf_ptr = 0;

    return true;
}

}