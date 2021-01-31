#pragma once

#include "Ray.h"

namespace mypt {

struct AABB {
    AABB() : _min(vec3()), _max(vec3()) {}
    AABB(const vec3& a, const vec3& b) : _min(a), _max(b) {}

    vec3 min() const { return _min; }
    vec3 max() const { return _max; }

    bool intersect(const Ray& r, Float tmin, Float tmax) const;

    Float surface_area() {
        return 2*(_max - _min).length_squared();
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "AABB : {" << std::endl;
        oss << "\tMin : " << _min << "," << std::endl;
        oss << "\tMax : " << _max << std::endl;
        oss << "}";
        return oss.str();
    }
private:
    vec3 _min;
    vec3 _max;
};

AABB surrounding(AABB box0, AABB box1);

}