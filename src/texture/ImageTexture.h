#pragma once

#include "../core/Texture.h"
#include "../core/Image.h"

/// TODO: 
///  - Treatment of UV (clamp, Loop, etc...) should be configured

class ImageTexture final : public Texture, Image<RGB> {
public:
    ImageTexture() : Image<RGB>(0, 0){}
    ImageTexture(const std::string& filename) : Image<RGB>(filename) {}

    virtual vec3 value(double u, double v, const vec3& p) const override;
};

// ----------------------------------------------------------------
vec3 ImageTexture::value(double u, double v, const vec3& p) const {
    // If data is not allocated, then return solid magenta as a debugging aid
    if(data == nullptr) return vec3(1, 0, 1);

    // Clanp input texture coordinates to [0, 1] x [1, 0]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);

    int i = static_cast<int>(u * width);
    int j = static_cast<int>(v * height);

    if(i >= width) i = width-1;
    if(j >= height) j = height-1;

    auto pixel = this->get(i, j);
    return vec3(pixel / 255.0f);
}

