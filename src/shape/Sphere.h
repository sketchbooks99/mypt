#pragma once

#include "../core/Shape.h"

namespace mypt {

class Sphere final : public Shape {
    public:
        Sphere() {}
        Sphere(vec3 cen, double r) : center(cen), radius(r) {};

        virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        virtual AABB bounding() const;
    private:
        vec2 getUV(const vec3& p) const {
            vec3 tmp = (p - center) / radius;
            auto phi = atan2(tmp.z, tmp.x);
            auto theta = asin(tmp.y);
            auto u = 1.0 - (phi + pi) / (2.0*pi);
            auto v = (theta + pi/2.0) / pi;
            return vec2(u, v);
        }
        vec3 center;
        double radius;
};

std::shared_ptr<Shape> createSphereShape(vec3 cen, double r);

}
