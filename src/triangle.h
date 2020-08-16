#ifndef triangle_h
#define triangle_h

#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
    public:
        triangle() {}
        triangle(vec3 p0, vec3 p1, vec3 p2, shared_ptr<material> m)
            : v{p0, p1, p2}, mat_ptr(m) {};
        
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const;

    public:
        vec3 v[3];
        shared_ptr<material> mat_ptr;

};

// See reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // compute normal
    vec3 v0v1 = v[1] - v[0];
    vec3 v0v2 = v[2] - v[0];
    auto normal = cross(v0v1, v0v2);
    auto area2 = normal.length();

    // Step 1: Finding P

    // Validation of ray and triangle intersection. 
    // If ray and triangle plane are parallel, return FALSE.
    float ndot_rdir = dot(normal, r.direction());
    float eps = 0.0001;
    if(fabs(ndot_rdir) < eps) 
        return false;

    // Compute d
    float d = dot(normal, v[0]);

    // Compute t
    float t = (dot(normal, r.origin()) + d) / ndot_rdir;
    // Validation of ray position with respect to triangle.
    if (t < 0) return false;

    // Compute the intersection point.
    auto p = r.origin() + t * r.direction();

    // Step 2: inside-outside test
    vec3 c; // vector perpendicular to triangle's plane

    // MEMO: What is "right side"? 
    // I have to create readme about this intesection algorithm.
    // Edge 0
    vec3 edge0 = v[1] - v[0];
    vec3 vp0 = p - v[0];
    c = cross(edge0, vp0);
    if (dot(normal, c) < 0) return false; // P is on the right side

    // Edge 1
    vec3 edge1 = v[2] - v[1];
    vec3 vp1 = p - v[1];
    c = cross(edge1, vp1);
    if (dot(normal, c) < 0) return false; // P is on the right side

    // Edge 2
    vec3 edge2 = v[0] - v[2];
    vec3 vp2 = p - v[2];
    c = cross(edge2, vp2);
    if (dot(normal, c) < 0) return false; // P is on the right side

    // This ray hits the triangle.
    rec.t = t;
    rec.p = p;
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;
    return true;
}

bool triangle::bounding_box(double t0, double t1, aabb& output_box) const {
    vec3 min, max;
    for(auto p : v) {
        if (p.x < min.x) min.x = p.x;
        if (p.x > max.x) max.x = p.x;

        if (p.y < min.y) min.y = p.y;
        if (p.y > max.y) max.y = p.y;

        if (p.z < min.z) min.z = p.z;
        if (p.z > max.z) max.z = p.z;
    }

    output_box = aabb(min, max);
    return true;
}

#endif