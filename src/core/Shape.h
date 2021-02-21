#pragma once

#include "AABB.h"
#include "Ray.h"
#include "Transform.h"
#include "Material.h"

namespace mypt {

enum class ShapeType {
    None,
    Sphere,
    MovingSphere,
    Plane,
    Triangle
};

inline std::ostream& operator<<(std::ostream& out, const ShapeType& type) {
    switch (type) {
    case ShapeType::Sphere:
        return out << "ShapeType::Shape";
    case ShapeType::MovingSphere:
        return out << "ShapeType::MovingSphere";
    case ShapeType::Plane:
        return out << "ShapeType::Plane";
    case ShapeType::Triangle:
        return out << "ShapeType::Triangle";
    default:
        return out << "";
    }
}

class Shape {
public:
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
    
    virtual double pdf_value(const vec3& /* o */, const vec3& /* v */) const { return 0.0; }
    virtual vec3 random(const vec3& /* o */) const { return vec3(1, 0, 0); }

    virtual ShapeType type() const = 0;
};

}

