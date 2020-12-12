#pragma once

#include "../core/Texture.h"

namespace mypt {

class CheckerTexture final : public Texture {
public:
    CheckerTexture() {}
    CheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1, int step=5) : even(t0), odd(t1), step(step) {}
    CheckerTexture(const vec3& color1, const vec3& color2)
    : odd(std::make_shared<ConstantTexture>(color1)), even(std::make_shared<ConstantTexture>(color2)) {}

    virtual vec3 value(double u, double v, const vec3& p) const {
        auto sines = sin(step*u) * sin(step*v);
        if(sines < 0) 
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }
    
private:
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;
    int step;
};

}
