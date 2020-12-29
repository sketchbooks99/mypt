#pragma once 

#include "../core/Shape.h"
#include "../core/Image.h"

namespace mypt {

class ImagePlane final : public Shape {
public:
    ImagePlane() {}
    ImagePlane(vec2 min, vec2 max, int width, int height)
    : min(min), max(max), image(Image<RGB>(width, height)) {}

    bool 
private:
    vec2 min, max;
    Image<RGB> image;
};

std::shared_ptr<Shape> createImagePlaneShape(vec2 min, vec2 max, int width, int height);

}