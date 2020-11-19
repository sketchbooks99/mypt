#pragma once

#include "AABB.h"
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
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Shape {
    public:
        virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
        virtual AABB bounding() const = 0;
};

