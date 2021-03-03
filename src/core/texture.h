#pragma once

#include "math_util.h"

namespace mypt {

/** TODO: 
 * Implement derivatives on texture coordiantes space to achieve mipmap.
 */ 

enum class TextureType {
    None,
    Constant,
    Checker,
    Image,
    Noise
};

inline std::ostream& operator<<(std::ostream& out, TextureType type) {
    switch(type) {
    case TextureType::Constant:
        return out << "TextureType::Constant";
        break;
    case TextureType::Checker:
        return out << "TextureType::Checker";
        break;
    case TextureType::Image:
        return out << "TextureType::Image";
        break;
    case TextureType::Noise:
        return out << "TextureType::Noise";
        break;
    default:
        Throw("This texture type is not supported.");
        break;
    }
}

class Texture {
public:
    virtual vec3 value(const vec2& uv, const vec3& p) const = 0;
    virtual std::string to_string() const = 0;
    virtual TextureType type() const = 0;
};

}