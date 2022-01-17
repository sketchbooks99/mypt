#pragma once

#include "vec.h"

namespace mypt {

class Ray {
public:
    Ray() {}
    Ray(const vec3& origin, const vec3& direction, Float time = 0.0)
    : orig(origin), dir(direction), tm(time)
    {}
    
    const vec3& origin() const     { return orig; }
    const vec3& direction() const  { return dir; }
    const Float& time() const     { return tm; }
    
    vec3 at(const Float& t) const {
        return orig + t * dir;
    }
    
private:
    vec3 orig;
    vec3 dir;
    Float tm;
};

}

