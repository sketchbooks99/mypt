#pragma once 

#include "../core/Shape.h"

class Plane final : public Shape {
public:
    enum class PlaneAxis { XY, YZ, XZ };
    Plane() {}
    Plane(vec2 min, vec2 max, double k, PlaneAxis axis)
    : min(min), max(max), k(k), axis(axis) {}

    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    virtual AABB bounding() const override;
private:
    vec2 min, max;  
    double k;       // Constant value of plane axis
    PlaneAxis axis;
};

std::shared_ptr<Shape> createPlaneShape(const vec2& min, const vec2& max, double k, Plane::PlaneAxis axis=Plane::PlaneAxis::XY);
