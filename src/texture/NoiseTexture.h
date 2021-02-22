#pragma once

#include "../core/Texture.h"
#include "../core/Perlin.h"

namespace mypt {

class NoiseTexture final : public Texture {
public:
    enum class Mode { NOISE, TURB };
    NoiseTexture() {}
    NoiseTexture(Float sc, Mode mode=Mode::NOISE) : scale(sc), mode(mode) {}

    vec3 value(Float /* u */, Float /* v */, const vec3& p) const override {
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

    Type type() const override { return Type::Noise; }
private:
    Perlin noise;
    Float scale;
    Mode mode;
};

}
