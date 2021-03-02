#pragma once

#include "../core/Shape.h"

namespace mypt {

class Sphere final : public Shape {
public:
    explicit Sphere() {}
    explicit Sphere(Float r) : radius(r) {};

    bool intersect(const Ray& r, Float t_min, Float t_max, HitRecord& rec) const;
    AABB bounding() const;
    Float pdf_value(const vec3& o, const vec3& v) const override;
    vec3 random(const vec3& o) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Sphere : {" << std::endl;
        oss << "\tRadius : " << radius << std::endl;
        oss << "}";
        return oss.str();
    }
private:
    vec2 getUV(const vec3& p) const;
    Float radius;
};

std::shared_ptr<Shape> createSphereShape(Float r);

}
