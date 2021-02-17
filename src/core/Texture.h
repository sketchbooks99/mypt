#pragma once

#include "MathUtil.h"

namespace mypt {

class Texture {
public:
    virtual vec3 value(Float u, Float v, const vec3& p) const = 0;
    virtual std::string to_string() const = 0;
};

}