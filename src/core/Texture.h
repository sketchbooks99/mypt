#pragma once

#include "MathUtil.h"

namespace mypt {

class Texture {
public:
    virtual vec3 value(double u, double v, const vec3& p) const = 0;
    virtual std::string to_string() const = 0;
};

}