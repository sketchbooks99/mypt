#include "disney.h"
#include "../core/color.h"

namespace mypt {

/** 
 * \todo Implemetation this.
 * 
 * \ref: https://rayspace.xyz/CG/contents/Disney_principled_BRDF/
 * 
 * EQUATION:
 * fr(wi,wo) = {lerp(fdiffuse(wi,wo), fsubsurface(wi,wo),subsurface) + fsheen(wi,wo)}(1-metallic)
 *           + fspecular(wi,wo) + fclearcoat(wi,wo)
 */
bool Disney::scatter(const Ray& r_in, SurfaceInteraction& si) const {
    auto wi = normalize(r_in.direction());
    auto h = normalize(vec3()); 
    /// \note cos_d is dot product of wi(wo) and half vector.
    auto cos_d = dot(si.n, h);
    auto fd90 = 0.5 + 2*m_roughness*cos_d*cos_d;
}

}