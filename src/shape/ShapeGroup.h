#pragma once

#include "../core/Shape.h"

namespace mypt {

class ShapeGroup final : public Shape {
public:
    ShapeGroup() : bbox(AABB()) {}
    ShapeGroup(std::vector<std::shared_ptr<Shape>> group) : group(group), bbox(AABB()) {}
    
    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override;

    double pdf_value(const vec3&, const vec3&) const override;
    vec3 random(const vec3&) const override;

    void append(std::shared_ptr<Shape> shape);
private:
    void calcBound();
    std::vector<std::shared_ptr<Shape>> group;
    AABB bbox;
};

}