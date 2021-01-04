#pragma once

#include "AABB.h"
#include "Ray.h"
#include "Transform.h"
#include "Material.h"

namespace mypt {

class Shape {
public:
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) = 0;
    virtual AABB bounding() = 0;
    
    virtual double pdf_value(const vec3& o, const vec3& v) { return 0.0; }
    virtual vec3 random(const vec3& o) { return vec3(1, 0, 0); }
};

}

