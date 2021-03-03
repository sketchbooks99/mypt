#include "plane.h"

namespace mypt {

// ----------------------------------------------------------------------------------
bool Plane::intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const {
    auto t = -r.origin().y / r.direction().y;
    if(t < t_min || t > t_max) 
        return false;
    
    Float x = r.origin().x + t * r.direction().x;
    Float z = r.origin().z + t * r.direction().z;
    if(x < min[0] || x > max[0] || z < min[1] || z > max[1]) 
        return false;

    // Store ray information at intesection point
    Float u = (x-min[0]) / (max[0]-min[0]);
    Float v = (z-min[1]) / (max[1]-min[1]);
    si.uv = vec2(u, v);
    si.t = t;
    vec3 outward_normal(0, 1, 0);
    si.set_face_normal(r, outward_normal);
    si.p = r.at(t);

    return true;
}

// ----------------------------------------------------------------------------------
AABB Plane::bounding() const {
    vec3 _min(min[0], -eps, min[1]);
    vec3 _max(max[0],  eps, max[1]);

    return AABB(_min, _max);
}

// ----------------------------------------------------------------------------------
Float Plane::pdf_value(const vec3& origin, const vec3& v) const {
    SurfaceInteraction si;
    if(!this->intersect(Ray(origin, v), eps, infinity, si))
        return 0;
    
    auto area = (max[0]-min[0])*(max[1]-min[1]);
    auto distance_squared = si.t * si.t * v.length_squared();
    auto cosine = fabs(dot(v, si.n) / v.length());

    return distance_squared / (cosine * area);
}

// ----------------------------------------------------------------------------------
vec3 Plane::random(const vec3& origin) const {
    auto random_point = vec3(random_float(min[0],max[0]), 0.0f, random_float(min[1], max[1]));
    return random_point - origin;
}

// ----------------------------------------------------------------------------------
std::shared_ptr<Shape> createPlaneShape(const vec2& min, const vec2& max)
{
    return std::make_shared<Plane>(min, max);
}

}