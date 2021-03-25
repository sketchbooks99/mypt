#include "noise.h"

namespace mypt {

vec3 NoiseTexture::value(const vec2& /* uv */, const vec3& p) const {
    switch(mode) {
    case Mode::NOISE:
        return vec3(1,1,1) * noise.noise(scale * p);
        break;
    case Mode::TURB:
        return vec3(1,1,1) * noise.turb(scale * p);
        break;
    default:
        Throw("This noise mode is not supported!\n");
        return vec3();
        break;
    }
}

std::string NoiseTexture::to_string() const {
    std::ostringstream oss;
    oss << "NoiseTexture : {" << std::endl;
    oss << "\tScale : " << scale << "," << std::endl;
    oss << "\tMode : " << mode << std::endl;
    oss << "}";
    return oss.str();
}

}