#pragma once

#include "Ray.h"

struct HitRecord;

// Abstract class 
class Material {
public:
    virtual vec3 emitted(double u, double v, const vec3& p) const {
        return vec3(0, 0, 0);
    }
    virtual bool scatter (
        const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
    ) const = 0;
};

