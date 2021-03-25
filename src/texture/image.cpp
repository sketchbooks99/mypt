#include "image.h"

namespace mypt {

// ----------------------------------------------------------------
vec3 ImageTexture::value(const vec2& uv, const vec3& /* p */) const {
    // If data aren't allocated, then return solid magenta as a debugging aid
    if(data == nullptr) return vec3(1, 0, 1);

    // Clamp input texture coordinates to [0, 1] x [1, 0]
    Float u = clamp(uv.x, 0.0, 1.0);
    Float v = 1.0 - clamp(uv.y, 0.0, 1.0);

    int i = static_cast<int>(u * width);
    int j = static_cast<int>(v * height);

    /** TODO: 
     * The different ways to clamp texture should be implemented, such as repeat/edge.
     */
    if(i >= width) i = width-1;
    if(j >= height) j = height-1;

    auto pixel = static_cast<vec3>(this->get(i, j));
    return pixel / 255.0f;
}

}