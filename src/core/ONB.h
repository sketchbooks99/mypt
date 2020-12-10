#pragma once 

#include "MathUtil.h"

// Orthonormal basis class
class ONB {
public:
    ONB() {}

    inline vec3 operator[](int i) const { return (&u)[i]; }

    vec3 local(double a, double b, double c) const {
        return a*u + b*v + c*w;
    }

    vec3 local(const vec3& a) const {
        return a.x*u + a.y*v + a.z*w;
    }

    void build_from_w(const vec3& n) {
        w = normalize(n);
        vec3 a = (fabs(w.x) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
        v = normalize(cross(w, a));
        u = cross(w, v); 
    }

    // normal, tangent, bitangent(?)
    vec3 u, v, w;
};