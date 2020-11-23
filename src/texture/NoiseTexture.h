#pragma once

#include "../core/Texture.h"
#include "../core/Perlin.h"

class NoiseTexture final : public Texture {
    public:
        NoiseTexture() {}
        NoiseTexture(double sc) : scale(sc) {}

        virtual vec3 value(double u, double v, const vec3& p) const {
            return vec3(1,1,1) * 0.5 * (1 + sin(scale * p.z + 10 * noise.turb(p)));
        }
    public:
        Perlin noise;
        double scale;
};
