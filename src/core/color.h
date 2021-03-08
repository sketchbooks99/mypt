#pragma once 

#include "vec.h"

namespace mypt {

inline RGB vec2color(const vec3& c, float scale) {
    // auto r = sqrt(scale * c.x);
    // auto g = sqrt(scale * c.y);
    // auto b = sqrt(scale * c.z);
    auto r = scale * c.x;
    auto g = scale * c.y;
    auto b = scale * c.z;
    RGB rgb_color(static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999)),
                    static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999)),
                    static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999)));
    return rgb_color;
}

// Conversion from RGB to luminance
inline Float luminance(const vec3& c) {
    return 0.2126*c.x + 0.7152*c.y + 0.0722*c.z;
}

}