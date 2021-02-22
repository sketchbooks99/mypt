#pragma once

#include "../core/Shape.h"

namespace mypt {

class MovingSphere final : public Shape {
public:
    MovingSphere() {}
    MovingSphere(
        vec3 cen0, vec3 cen1, Float t0, Float t1, Float r)
        : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r)
    {};

    bool intersect(const Ray& r, Float tmin, Float tmax, HitRecord& rec) const override;
    AABB bounding() const override;

    vec3 get_center(Float time) const;

    Type type() const override { return Type::MovingSphere; }

public:
    vec3 center0, center1;
    Float time0, time1;
    Float radius;
};

std::shared_ptr<Shape> createMovingSphere(vec3 cen0, vec3 cen1, Float t0, Float t1, Float r);

}