#pragma once

#include "AABB.h"
#include "Ray.h"
#include "Transform.h"
#include "Material.h"

namespace mypt {

class Shape {
public:
    enum class Type {
        None,
        Sphere,
        MovingSphere,
        Plane,
        Triangle
    };

    virtual bool intersect(const Ray& r, Float t_min, Float t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
    
    virtual Float pdf_value(const vec3& /* o */, const vec3& /* v */) const { return 0.0; }
    virtual vec3 random(const vec3& /* o */) const { return vec3(1, 0, 0); }

    virtual Type type() const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const Shape::Type& type) {
    switch (type) {
    case Shape::Type::Sphere:
        return out << "Shape::Type::Shape";
    case Shape::Type::MovingSphere:
        return out << "Shape::Type::MovingSphere";
    case Shape::Type::Plane:
        return out << "Shape::Type::Plane";
    case Shape::Type::Triangle:
        return out << "Shape::Type::Triangle";
    default:
        return out << "";
    }
}

}

