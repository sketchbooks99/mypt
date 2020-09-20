//
//  Ray.h
//  RayTracing
//
//  Created by 木内舜司 on 2020/04/11.
//  Copyright © 2020 木内舜司. All rights reserved.
//

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
public:
    Ray() {}
    Ray(const vec3& origin, const vec3& direction, double time = 0.0)
    : orig(origin), dir(direction), tm(time)
    {}
    
    vec3 origin() const     { return orig; }
    vec3 direction() const  { return dir; }
    double time() const     { return tm; }
    
    vec3 at(double t) const {
        return orig + t * dir;
    }
    
public:
    vec3 orig;
    vec3 dir;
    double tm;
};


#endif /* Ray_h */
