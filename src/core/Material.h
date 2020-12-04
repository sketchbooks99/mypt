#pragma once

#include "Ray.h"

class Material;

struct HitRecord {
    vec3 p;
    vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
        // front_face = dot(r.direction(), outward_normal) < 0;
        // normal = front_face ? outward_normal : -outward_normal;
        normal = outward_normal;
    }
};

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

