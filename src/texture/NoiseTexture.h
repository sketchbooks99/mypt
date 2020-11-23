#pragma once

#include "../core/Texture.h"
#include "../core/Perlin.h"

class NoiseTexture final : public Texture {
public:
    enum class Mode { NOISE, TURB };
    NoiseTexture() {}
    NoiseTexture(double sc, Mode mode=Mode::NOISE) : scale(sc), mode(mode) {}

    virtual vec3 value(double u, double v, const vec3& p) const {
        // return vec3(1,1,1) * 0.5 * (1 + sin(scale * p.z + 10 * noise.turb(p)));
        switch(mode) {
        case Mode::NOISE:
            return vec3(1,1,1) * noise.noise(scale * p);
            break;
        case Mode::TURB:
            return vec3(1,1,1) * noise.turb(scale * p);
            break; 
        default:
            throw std::runtime_error("This noise mode is not supported!\n");
        }
    }
private:
    Perlin noise;
    double scale;
    Mode mode;
};
