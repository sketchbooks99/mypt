#pragma once

#include "../core/Shape.h"

namespace mypt {

class MovingSphere final : public Shape {
    public:
        MovingSphere() {}
        MovingSphere(
            vec3 cen0, vec3 cen1, double t0, double t1, double r)
            : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r)
        {};

        bool intersect(const Ray& r, double tmin, double tmax, HitRecord& rec) const override;
        AABB bounding() const override;

        vec3 get_center(double time) const;

    public:
        vec3 center0, center1;
        double time0, time1;
        double radius;
};

std::shared_ptr<Shape> createMovingSphere(vec3 cen0, vec3 cen1, double t0, double t1, double r);

}