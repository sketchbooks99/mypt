#pragma once

#include "../core/texture.h"

namespace mypt {

class CheckerTexture final : public Texture {
public:
    explicit CheckerTexture() {}
    CheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1, Float scale=5)
    : color1(t1), color2(t0), m_scale(scale) {}
    CheckerTexture(const vec3& color1, const vec3& color2, Float scale=5)
    : color1(std::make_shared<ConstantTexture>(color1)), 
      color2(std::make_shared<ConstantTexture>(color2)), 
      m_scale(scale) {}

    vec3 value(const vec2& uv, const vec3& p) const override {
        auto sines = sin(m_scale*uv.x) * sin(m_scale*uv.y);
        if(sines < 0) 
            return color1->value(uv, p);
        else
            return color2->value(uv, p);
    }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "CheckerTexture : {" << std::endl;
        oss << "\tColor1 : " << color1 << std::endl;
        oss << "\tColor2 : " << color2 << std::endl;
        oss << "\tm_scale : " << m_scale << std::endl;
        oss << "}";
        return oss.str();
    }

    TextureType type() const override { return TextureType::Checker; }
    
private:
    std::shared_ptr<Texture> color1;
    std::shared_ptr<Texture> color2;
    Float m_scale;
};

}
