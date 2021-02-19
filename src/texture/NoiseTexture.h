#pragma once

#include "../core/Texture.h"
#include "../core/Perlin.h"

namespace mypt {

class NoiseTexture final : public Texture {
public:
    enum class Mode { NOISE, TURB };
    NoiseTexture() {}
    NoiseTexture(Float sc, Mode mode=Mode::NOISE) : scale(sc), mode(mode) {}

    vec3 value(Float /* u */, Float /* v */, const vec3& p) const override;

    std::string to_string() const override;

    TextureType type() const override { return TextureType::Noise; }
private:
    Perlin noise;
    Float scale;
    Mode mode;
};

inline std::ostream& operator<<(std::ostream &out, NoiseTexture::Mode m) {
    switch(m) {
    case NoiseTexture::Mode::NOISE:
        return out << "NoiseTexture::Mode::NOISE";
        break;
    case NoiseTexture::Mode::TURB:
        return out << "NoiseTexture::Mode::TURB";
        break;
    default:
        return out << "";
        break;
    }
}

}
