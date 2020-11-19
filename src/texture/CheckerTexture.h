#pragma once

#include "../core/Texture.h"

class CheckerTexture : public Texture {
    public:
        CheckerTexture() {}
        CheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1) : even(t0), odd(t1) {}

        virtual vec3 value(double u, double v, const vec3& p) const {
            auto sines = sin(20*u) * sin(20*v);
            if(sines < 0) 
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
        }
        
    public:
        std::shared_ptr<Texture> odd;
        std::shared_ptr<Texture> even;
};

