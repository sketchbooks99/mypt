#pragma once

#include "../core/Texture.h"

namespace mypt {

class ConstantTexture final : public Texture {
public:
    ConstantTexture(){}
    ConstantTexture(vec3 c) : color(c) {}

    virtual vec3 value(double u, double v, const vec3& p) const {
        return color;
    }

private:
    vec3 color;
};

}