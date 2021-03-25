#pragma once

#include "aabb.h"
#include "ray.h"
#include "transform.h"
#include "material.h"

namespace mypt {

class Shape {
public:
    virtual bool intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const = 0;
    virtual AABB bounding() const = 0;
    
    virtual Float pdf_value(const vec3& /* o */, const vec3& /* v */) const { return 0.0; }
    virtual vec3 random(const vec3& /* o */) const { return vec3(1, 0, 0); }

    virtual std::string to_string() const = 0;
};

}

