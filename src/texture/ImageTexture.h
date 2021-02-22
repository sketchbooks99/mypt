#pragma once

#include "../core/Texture.h"
#include "../core/Image.h"

/// TODO: 
///  - Treatment of UV (clamp, Loop, etc...) should be configured

namespace mypt {

class ImageTexture final : public Texture, public Image<RGB> {
public:
    ImageTexture() : Image<RGB>(0, 0){}
    ImageTexture(const std::string& filename) : Image<RGB>(filename) {}

    vec3 value(Float u, Float v, const vec3& p) const override;

    Type type() const override { return Type::Image; }
};

}

