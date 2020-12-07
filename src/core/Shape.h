#pragma once

#include "AABB.h"
#include "Ray.h"
#include "Material.h"
#include "Transform.h"

class Shape {
public:
    Shape() : transform(std::shared_ptr<Transform>()) {}
    Shape(std::shared_ptr<Transform> transform) : transform(transform) {}
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
private:
    std::shared_ptr<Transform> transform;
};

