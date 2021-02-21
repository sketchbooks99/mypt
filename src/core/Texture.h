#pragma once

#include "MathUtil.h"

namespace mypt {

enum class TextureType {
    Constant, 
    Checker, 
    Noise, 
    Image
};

inline std::ostream& operator<<(std::ostream& out, const TextureType& type) {
    switch(type) {
    case TextureType::Constant:
        return out << "TextureType::Constant";
    case TextureType::Checker:
        return out << "TextureType::Checker";
    case TextureType::Noise:
        return out << "TextureType::Noise";
    case TextureType::Image:
        return out << "TextureType::Image";
    default:
        return out << "";
    }
}

class Texture {
public:
    virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

}