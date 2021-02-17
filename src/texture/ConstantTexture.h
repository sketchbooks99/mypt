#pragma once

#include "../core/Texture.h"

namespace mypt {

class ConstantTexture final : public Texture {
public:
    ConstantTexture(){}
    ConstantTexture(vec3 c) : color(c) {}

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
private:
    vec3 color;
};

}