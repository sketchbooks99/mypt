#pragma once

#include "../core/texture.h"
#include "../core/image.h"

/// TODO: 
///  - Treatment of UV (clamp, Loop, etc...) should be configured

namespace mypt {

class ImageTexture final : public Texture, public Image<RGB> {
public:
    explicit ImageTexture() : Image<RGB>(0, 0){}
    explicit ImageTexture(const std::string& filename) : Image<RGB>(filename) {}

    vec3 value(const vec2& uv, const vec3& p) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "ImageTexture : {" << std::endl;
        oss << "\tResolution : " << "[" << this->getWidth() << ", ";
        oss << this->getHeight() << "]," << std::endl;
        oss << "}";
        return oss.str();
    }

    TextureType type() const override { return TextureType::Image; }
};

}

