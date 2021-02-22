#pragma once

#include "../core/Texture.h"

namespace mypt {

class ConstantTexture final : public Texture {
public:
    ConstantTexture(){}
    ConstantTexture(vec3 c) : color(c) {}

    vec3 value(Float /* u */, Float /* v */, const vec3& /* p */) const override {
        return color;
    }

    Type type() const override { return Type::Constant; }
private:
    vec3 color;
};

}