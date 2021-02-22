#pragma once

#include "../core/Shape.h"

namespace mypt {

class Sphere final : public Shape {
public:
    Sphere() {}
    Sphere(Float r) : radius(r) {};

    bool intersect(const Ray& r, Float t_min, Float t_max, HitRecord& rec) const override;
    AABB bounding() const override;
    Float pdf_value(const vec3& o, const vec3& v) const override;
    vec3 random(const vec3& o) const override;

    Type type() const override { return Type::Sphere; }
private:
    vec2 getUV(const vec3& p) const;

    Float radius;
};

std::shared_ptr<Shape> createSphereShape(Float r);

}
