#pragma once

#include "../core/texture.h"
#include "../core/perlin.h"

namespace mypt {

class NoiseTexture final : public Texture {
public:
    enum class Mode { NOISE, TURB };
    explicit NoiseTexture() {}
    explicit NoiseTexture(Float sc, Mode mode=Mode::NOISE) : scale(sc), mode(mode) {}

    vec3 value(const vec2& /* uv */, const vec3& p) const override;

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
