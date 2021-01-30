#include "NoiseTexture.h"

namespace mypt {

vec3 NoiseTexture::value(double /* u */, double /* v */, const vec3& p) const {
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

std::string NoiseTexture::to_string() const {
    std::ostringstream oss;
    oss << "NoiseTexture : {" << std::endl;
    oss << "\tScale : " << scale << "," << std::endl;
    oss << "\tMode : " << mode << std::endl;
    oss << "}";
    return oss.str();
}

}