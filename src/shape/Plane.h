#pragma once 

#include "../core/Shape.h"

class Plane final : public Shape {
public:
    Plane() {}
    Plane(vec2 min, vec2 max) : min(min), max(max) {}

    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    virtual AABB bounding() const override;
private:
    vec2 min, max;
};

std::shared_ptr<Shape> createPlaneShape(const vec2& min, const vec2& max);
