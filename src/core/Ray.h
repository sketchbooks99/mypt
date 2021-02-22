#pragma once

#include "MathUtil.h"

namespace mypt {

class Ray {
public:
    Ray() {}
    Ray(const vec3& origin, const vec3& direction, Float time = 0.0, RGBA c = RGBA(0))
    : orig(origin), dir(direction), tm(time), c(c)
    {}
    
    vec3 origin() const     { return orig; }
    vec3 direction() const  { return dir; }
    Float time() const     { return tm; }
    RGBA color() const         { return c; }
    void set_color(RGBA color) { c = color; }
    
    vec3 at(Float t) const {
        return orig + t * dir;
    }
    
private:
    vec3 orig;
    vec3 dir;
    Float tm;
    RGBA c;
};

}

