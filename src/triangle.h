#ifndef triangle_h
#ifndef triangle_h

#include "hittable.h"
#include "vec3.h"

class triangle : public triangle {
    public:
        triangle() {}
        triangle(vec3 p0, vec3 p1, vec3 p2, shared_ptr<material> m)
            : v0(p0), v1(p1), v2(p2), mat_ptr(m) {};
        
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const;

    public:
        vec3 v0, v1, v2;
        shared_ptr<material> mat_ptr;

};

// See reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // compute normal
    vec3 v0v1 = v1 - v0;
    vec3 v0v2 = v2 - v0;
    auto normal = unit_vector(cross(v0v1, v0v2));

    // Step 1: Finding P

    // Validation of ray and triangle intersection. 
    // If ray and triangle plane are parallel, return FALSE.
    float ndot_rdir = dot(normal, r.direction());
    float eps = 0.0001;
    if(fabs(ndot_rdir) < eps) 
        return false;

    // Compute d
    float d = dot(normal, v0);

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
    vec3 edge0 = v1 - v0;
    vec3 vp0 = p - v0;
    c = cross(edge0, vp0);
    if (dot(normal, c) < 0) return false; // P is on the right side

    // Edge 1
    vec3 edge1 = v2 - v1;
    vec3 vp1 = p - v1;
    c = cross(edge1, vp1);
    if (dot(normal, c) < 0) return false; // P is on the right side

    // Edge 2
    vec3 edge2 = v0 - v2;
    vec3 vp2 = p - v2;
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
    center = 
}