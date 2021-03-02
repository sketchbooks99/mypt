#pragma once

#include "../core/Shape.h"

namespace mypt {

class MovingSphere final : public Shape {
public:
    explicit MovingSphere() {}
    explicit MovingSphere(
        vec3 cen0, vec3 cen1, Float t0, Float t1, Float r)
        : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r)
    {};

    bool intersect(const Ray& r, Float tmin, Float tmax, HitRecord& rec) const;
    AABB bounding() const;

    vec3 center(Float time) const;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "FilpFace : {" << std::endl;
        oss << "\tCenter0 : " << center0 << ", ";
        oss << "\tCenter1 : " << center1 << ", " << std::endl;
        oss << "\tTime0 : " << time0 << ", ";
        oss << "\tTime1 : " << time1 << ", " << std::endl;
        oss << "\tRadius : " << radius << std::endl;
        oss << "}";
        return oss.str();
    }

public:
    vec3 center0, center1;
    Float time0, time1;
    Float radius;
};

std::shared_ptr<Shape> createMovingSphere(vec3 cen0, vec3 cen1, Float t0, Float t1, Float r);

}