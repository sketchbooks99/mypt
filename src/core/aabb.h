#pragma once

#include "ray.h"

namespace mypt {

/** \brief Axis Aligned Bounding Box. */
struct AABB {
    AABB() : m_min(vec3()), m_max(vec3()) {}
    AABB(const vec3& a, const vec3& b) : m_min(a), m_max(b) {}

    vec3 min() const { return m_min; }
    vec3 max() const { return m_max; }

    bool intersect(const Ray& r, Float t_min, Float t_max) const;
    
    Float surface_area() {
        Float dx = m_max.x - m_min.x;
        Float dy = m_max.y - m_min.y;
        Float dz = m_max.z - m_min.z;
        return 2*(dx*dy + dy*dz + dz*dx);
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "AABB : {" << std::endl;
        oss << "\tMin : " << m_min << "," << std::endl;
        oss << "\tMax : " << m_max << std::endl;
        oss << "}";
        return oss.str();
    }
private:
    vec3 m_min;
    vec3 m_max;
};

AABB surrounding(const AABB& box0, const AABB& box1);

}