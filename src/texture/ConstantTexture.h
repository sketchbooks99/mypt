#pragma once

#include "../core/Texture.h"

namespace mypt {

class ConstantTexture final : public Texture {
public:
    explicit ConstantTexture(){}
    explicit ConstantTexture(vec3 c) : color(c) {}

    vec3 value(Float /* u */, Float /* v */, const vec3& /* p */) const {
        return color;
    }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "ConstantTexture : {" << std::endl;
        oss << "\tColor : " << color << std::endl;
        oss << "}";
        return oss.str();
    }

    TextureType type() const override { return TextureType::Constant; }
private:
    vec3 color;
};

}