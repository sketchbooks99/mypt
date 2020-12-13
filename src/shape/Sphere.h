#pragma once

#include "../core/Shape.h"

namespace mypt {

class Sphere final : public Shape {
    public:
        Sphere() {}
        Sphere(double r) : radius(r) {};

        bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        AABB bounding() const;
        double pdf_value(const vec3& o, const vec3& v) const override;
        vec3 random(const vec3& o) const override;
    private:
        vec2 getUV(const vec3& p) const {
            vec3 tmp = p / radius;
            auto phi = atan2(tmp.z, tmp.x);
            auto theta = asin(tmp.y);
            auto u = 1.0 - (phi + pi) / (2.0*pi);
            auto v = (theta + pi/2.0) / pi;
            return vec2(u, v);
        }
        double radius;
};

std::shared_ptr<Shape> createSphereShape(double r);

}
