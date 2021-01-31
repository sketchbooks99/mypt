#pragma once

#include "../core/Texture.h"
#include "../core/Perlin.h"

namespace mypt {

class NoiseTexture final : public Texture {
public:
    enum class Mode { NOISE, TURB };
    NoiseTexture() {}
    NoiseTexture(double sc, Mode mode=Mode::NOISE) : scale(sc), mode(mode) {}

    vec3 value(double /* u */, double /* v */, const vec3& p) const override;

    std::string to_string() const override;
private:
    Perlin noise;
    double scale;
    Mode mode;
};

inline std::ostream& operator<<(std::ostream &out, NoiseTexture::Mode m) {
    switch(m) {
    case NoiseTexture::Mode::NOISE:
        return out << "NoiseTexture::Mode::NOISE";
    case NoiseTexture::Mode::TURB:
        return out << "NoiseTexture::Mode::TURB";
    default:
        return out << "";
    }
}

}
