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

// ShapePrimitive ----------------------------------------------------------------------
bool ShapePrimitive::intersect(Ray& r, double t_min, double t_max, HitRecord& rec) const {
    Ray tr_ray = *transform * r;
    if(!shape->intersect(tr_ray, t_min, t_max, rec))
        return false;
    
    auto p = rec.p;
    auto normal = rec.normal;
    p = mat4::point_mul(transform->getMatrix(), rec.p);
    normal = normalize(mat4::normal_mul(transform->getInvMatrix(), rec.normal));

    rec.p = p;
    rec.set_face_normal(r, normal);
    rec.mat_ptr = material;

    return true;
}

AABB ShapePrimitive::bounding() const {
    vec3 min(infinity, infinity, infinity);
    vec3 max(-infinity, -infinity, -infinity);

    for(int i=0; i<2; i++) {            // 0: min.x, 1: max.x
        for(int j=0; j<2; j++) {        // 0: min.y, 1: max.y
            for(int k=0; k<2; k++) {    // 0: min.z, 1: max.z
                auto x = (1-i)*shape->bounding().min().x + i*shape->bounding().max().x;
                auto y = (1-j)*shape->bounding().min().y + j*shape->bounding().max().y;
                auto z = (1-k)*shape->bounding().min().z + k*shape->bounding().max().z;
                
                vec3 tr_corner = mat4::point_mul(transform->getMatrix(), vec3(x, y, z));
                for(int l=0; l<3; l++) {
                    min[l] = fmin(min[l], tr_corner[l]);
                    max[l] = fmax(max[l], tr_corner[l]);
                }
            } 
        }
    }

    return AABB(min, max);
}

double ShapePrimitive::pdf_value(const vec3& o, const vec3& v) const {
    vec3 origin = mat4::point_mul(transform->getInvMatrix(), o);
    vec3 vec = mat4::vector_mul(transform->getInvMatrix(), v);
    return shape->pdf_value(origin, vec);
    // return shape->pdf_value(o, v);
}

vec3 ShapePrimitive::random(const vec3& o) const {
    return mat4::point_mul(transform->getMatrix(), shape->random(o));
}

// ConstantMedium ----------------------------------------------------------------------
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