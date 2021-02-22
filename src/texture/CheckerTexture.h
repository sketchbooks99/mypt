#pragma once

#include "../core/Texture.h"

namespace mypt {

class CheckerTexture final : public Texture {
public:
    CheckerTexture() {}
    CheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1, int step=5) : odd(t1), even(t0), step(step) {}
    CheckerTexture(const vec3& color1, const vec3& color2, int step=5)
    : odd(std::make_shared<ConstantTexture>(color1)), even(std::make_shared<ConstantTexture>(color2)), step(step) {}

    vec3 value(Float u, Float v, const vec3& p) const override {
        auto sines = sin(step*u*pi) * sin(step*v*pi);
        if(sines < 0) 
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }

    Type type() const override { return Type::Checker; }
    
private:
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;
    int step;
};

}
