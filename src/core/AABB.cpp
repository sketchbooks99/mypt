#include "AABB.h"

bool AABB::intersect(const Ray& r, double tmin, double tmax) const {
    for(int a = 0; a < 3; a++) {
        // std::cout << "min: " << _min << std::flush;
        // std::cout << ", max: " << _max << std::flush;
        auto t0 = ffmin((_min[a] - r.origin()[a]) / r.direction()[a],
                        (_max[a] - r.origin()[a]) / r.direction()[a]);
        auto t1 = ffmax((_min[a] - r.origin()[a]) / r.direction()[a],
                        (_max[a] - r.origin()[a]) / r.direction()[a]);
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