#pragma once

#include "AABB.h"
#include "Ray.h"
#include "Material.h"
#include "Transform.h"

namespace mypt {

class Shape {
public:
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
};

}

