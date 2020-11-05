#pragma once

#include "Util.h"

struct HitRecord;

// Abstract class 
class Material {
    public:
        virtual bool scatter (
            const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
        ) const = 0;
};

