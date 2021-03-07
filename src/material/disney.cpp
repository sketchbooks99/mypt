#include "disney.h"

namespace mypt {

/** EQUATION:
 * fr(wi,wo) = {lerp(fdiffuse(wi,wo), fsubsurface(wi,wo),subsurface) + fsheen(wi,wo)}(1-metallic)
 *           + fspecular(wi,wo) + fclearcoat(wi,wo)
 */
bool Disney::scatter(const Ray& r_in, SurfaceInteraction& si) const {

}

}