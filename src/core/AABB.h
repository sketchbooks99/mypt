#pragma once

#include "Ray.h"

struct AABB {
    AABB() : _min(vec3()), _max(vec3()) {}
    AABB(const vec3& a, const vec3& b) : _min(a), _max(b) {}

    vec3 min() const { return _min; }
    vec3 max() const { return _max; }

    bool intersect(const Ray& r, double tmin, double tmax) const;

    double surface_area() {
        return 2*(_max - _min).length_squared();
    }
private:
    vec3 _min;
    vec3 _max;
};

AABB surrounding(AABB box0, AABB box1);

