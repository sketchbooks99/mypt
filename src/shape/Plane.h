#pragma once 

#include "../core/Shape.h"

namespace mypt {

class Plane final : public Shape {
public:
    Plane() {}
    Plane(vec2 min, vec2 max) : min(min), max(max) {}

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override;

    double pdf_value(const vec3&, const vec3&) const override;
    vec3 random(const vec3&) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "FilpFace : {" << std::endl;
        oss << "\tMin : " << min << std::endl;
        oss << "\tMax : " << max << std::endl;
        oss << "}";
        return oss.str();
    }
private:
    vec2 min, max;
};

std::shared_ptr<Shape> createPlaneShape(const vec2& min, const vec2& max);
std::vector<std::shared_ptr<Shape>> createBoxShape(const vec3& min, const vec3& max);

}
