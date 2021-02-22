#pragma once

#include "MathUtil.h"

namespace mypt {

class Texture {
public:
    enum class Type {
        Constant, 
        Checker, 
        Noise, 
        Image
    };

    virtual vec3 value(Float u, Float v, const vec3& p) const = 0;
    virtual Type type() const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const Texture::Type& type) {
    switch(type) {
    case Texture::Type::Constant:
        return out << "Texture::Type::Constant";
    case Texture::Type::Checker:
        return out << "Texture::Type::Checker";
    case Texture::Type::Noise:
        return out << "Texture::Type::Noise";
    case Texture::Type::Image:
        return out << "Texture::Type::Image";
    default:
        return out << "";
    }
}

}