#include "Primitive.h"

/** NOTE: 
 * The ray origins must be inside the volume, so we have to carefully
 * treat intersection algorithm.
 * 
 * This code assumes that once a ray exists the constant medium boundary,
 * it will continue forever outside the boundary. Put another way,
 * it assumes that the boundary shape is convex. So this particular 
 * implemention will work for boundaries like boxes or spheres, but will
 * not work with toruses or shapes that contain voids. **/

namespace mypt {

bool ConstantMedium::intersect(Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // Print occasional samples when debugging. To enable, set enableDebug true.
    const bool enableDebug = false;
    const bool debugging = enableDebug && random_double() < 1e-4f;

    HitRecord rec1, rec2;

    if (!boundary->intersect(r, -infinity, infinity, rec1))
        return false;
    
    if (!boundary->intersect(r, rec1.t+1e-3f, infinity, rec2))
        return false;

    if (debugging) 
        std::cerr << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << '\n';

    rec1.t = fmin(rec1.t, t_min);
    rec2.t = fmax(rec2.t, t_max);

    if (rec1.t >= rec2.t) return false;
    
    if (rec1.t < 0) rec1.t = 0;

    const auto ray_length = r.direction().length();
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    const auto hit_distance = neg_inv_density * log(random_double());

    if (hit_distance > distance_inside_boundary)
        return false;
    
    rec.t = rec1.t + hit_distance / ray_length;
    rec.p = r.at(rec.t);

    if (debugging) {
        std::cerr << "hit_distance = " <<  hit_distance << '\n'
                  << "rec.t = " <<  rec.t << '\n'
                  << "rec.p = " <<  rec.p << '\n';
    }

    rec.normal = vec3(1,0,0); // arbitrary
    rec.front_face = true;    // arbitrary
    
    return true;
}

}