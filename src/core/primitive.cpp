#include "primitive.h"

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

ShapePrimitive::ShapePrimitive(
    std::shared_ptr<Shape> shape, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform
) : shape(shape), material(material), transform(transform)
{
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

    bbox = AABB(min, max);
}

// ShapePrimitive ----------------------------------------------------------------------
bool ShapePrimitive::intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const {
    Ray tr_ray = *transform * r;
    if(!shape->intersect(tr_ray, t_min, t_max, si))
        return false;
    
    auto p = si.p;
    auto normal = si.n;
    
    p = mat4::point_mul(transform->getMatrix(), si.p);
    normal = normalize(mat4::normal_mul(transform->getInvMatrix(), si.n));

    si.p = p;
    si.n = normal;
    si.mat_ptr = material;

    return true;
}

AABB ShapePrimitive::bounding() const {
    return bbox;
}

Float ShapePrimitive::pdf_value(const vec3& o, const vec3& v) const {
    vec3 origin = mat4::point_mul(transform->getInvMatrix(), o);
    vec3 vec = mat4::vector_mul(transform->getInvMatrix(), v);
    return shape->pdf_value(origin, vec);
}

vec3 ShapePrimitive::random(const vec3& o) const {
    return mat4::point_mul(transform->getMatrix(), shape->random(o));
}

// ConstantMedium ----------------------------------------------------------------------
bool ConstantMedium::intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const {
    // Print occasional samples when debugging. To enable, set enableDebug true.
    const bool enableDebug = false;
    const bool debugging = enableDebug && random_float() < 1e-4f;

    SurfaceInteraction si1, si2;

    if (!boundary->intersect(r, -infinity, infinity, si1))
        return false;
    
    if (!boundary->intersect(r, si1.t+1e-3f, infinity, si2))
        return false;

    if (debugging) 
        std::cerr << "\nt_min=" << si1.t << ", t_max=" << si2.t << '\n';

    si1.t = fmin(si1.t, t_min);
    si2.t = fmax(si2.t, t_max);

    if (si1.t >= si2.t) return false;
    
    if (si1.t < 0) si1.t = 0;

    const auto ray_length = r.direction().length();
    const auto distance_inside_boundary = (si2.t - si1.t) * ray_length;
    const auto hit_distance = neg_inv_density * log(random_float());

    if (hit_distance > distance_inside_boundary)
        return false;
    
    si.t = si1.t + hit_distance / ray_length;
    si.p = r.at(si.t);

    if (debugging) {
        std::cerr << "hit_distance = " <<  hit_distance << '\n'
                  << "si.t = " <<  si.t << '\n'
                  << "si.p = " <<  si.p << '\n';
    }

    si.n = vec3(1,0,0);     // arbitrary
    si.front_face = true;   // arbitrary
    
    return true;
}

}