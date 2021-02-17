#include "AABB.h"

namespace mypt {

bool AABB::intersect(const Ray& r, Float tmin, Float tmax) const {
    /** TIPS: The computation time in this intersection test 
     *        is significantly improved by closely storing values 
     *        in memory space. */
    
    vec3 v[6] = {
        vec3(_min.x, r.origin().x, r.direction().x),
        vec3(_max.x, r.origin().x, r.direction().x),
        vec3(_min.y, r.origin().y, r.direction().y),
        vec3(_max.y, r.origin().y, r.direction().y),
        vec3(_min.z, r.origin().z, r.direction().z),
        vec3(_max.z, r.origin().z, r.direction().z)
    };

    for(int a = 0; a < 3; a++) {
        /// FASTCODE:
        auto t0 = ffmin((v[a*2].x - v[a*2].y) / v[a*2].z,
                        (v[a*2+1].x - v[a*2+1].y) / v[a*2+1].z);
        auto t1 = ffmax((v[a*2].x - v[a*2].y) / v[a*2].z,
                        (v[a*2+1].x - v[a*2+1].y) / v[a*2+1].z);
                        
        /// SLOWCODE:
        // auto t0 = ffmin((_min[a] - r.origin()[a]) / r.direction()[a],
        //                 (_max[a] - r.origin()[a]) / r.direction()[a]);
        // auto t1 = ffmax((_min[a] - r.origin()[a]) / r.direction()[a],
        //                 (_max[a] - r.origin()[a]) / r.direction()[a]);

        tmin = ffmax(t0, tmin);
        tmax = ffmin(t1, tmax);
        if(tmax <= tmin)
            return false;
    }
    return true;
}

AABB surrounding(AABB box0, AABB box1) {
    vec3 small(ffmin(box0.min().x, box1.min().x),
               ffmin(box0.min().y, box1.min().y),
               ffmin(box0.min().z, box1.min().z));
    vec3 big  (ffmax(box0.max().x, box1.max().x),
               ffmax(box0.max().y, box1.max().y),
               ffmax(box0.max().z, box1.max().z));
    return AABB(small, big);
}

}