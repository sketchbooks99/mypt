#pragma once

#include "ray.h"

namespace mypt {

/** \brief Axis Aligned Bounding Box. */
struct AABB {
    AABB() : _min(vec3()), _max(vec3()) {}
    AABB(const vec3& a, const vec3& b) : _min(a), _max(b) {}

    vec3 min() const { return _min; }
    vec3 max() const { return _max; }

    bool intersect(const Ray& r, Float t_min, Float t_max) const;
    
    Float surface_area() {
        Float dx = _max.x - _min.x;
        Float dy = _max.y - _min.y;
        Float dz = _max.z - _min.z;
        return 2*(dx*dy + dy*dz + dz*dx);
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