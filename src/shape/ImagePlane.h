#pragma once 

#include "../core/vec3.h"
#include "../core/Shape.h"
#include "../core/Image.h"

namespace mypt {

class ImagePlane final : public Shape {
public:
    ImagePlane(vec2 min, vec2 max, int width, int height) 
    : min(min), max(max), image(Image<RGB>(width, height)) {}

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec);
    AABB bounding() override;

    double pdf_value(const vec3&, const vec3&) override;
    vec3 random(const vec3&) override;
private:
    vec2 min, max;
    Image<RGB> image; 
};

}
