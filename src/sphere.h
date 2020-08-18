#ifndef Sphere_h
#define Sphere_h

#include "Hittable.h"
#include "vec3.h"

class Sphere: public Hittable {
    public:
        Sphere() {}
        Sphere(vec3 cen, double r, shared_ptr<Material> m)
            : center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, AABB& output_box) const;
    public:
        vec3 center;
        double radius;
        shared_ptr<Material> mat_ptr;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const {
    // vector from origin to center
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            // std::cerr << "Sphere intersected.\n" << std::flush;
            return true;
        }
        temp = (-half_b + root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            // std::cerr << "Sphere intersected.\n" << std::flush;
            return true;
        }
    }
    return false;
}

bool Sphere::bounding_box(double t0, double t1, AABB& output_box) const {
    output_box = AABB(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
    return true;
}

#endif
