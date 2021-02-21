#pragma once

#include "../core/Shape.h"

namespace mypt {

class Sphere final : public Shape {
public:
    Sphere() {}
    Sphere(double r) : radius(r) {};

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override;
    double pdf_value(const vec3& o, const vec3& v) const override;
    vec3 random(const vec3& o) const override;

    ShapeType type() const override { return ShapeType::Sphere; }
private:
    vec2 getUV(const vec3& p) const;

    double radius;
};

std::shared_ptr<Shape> createSphereShape(double r);

}
