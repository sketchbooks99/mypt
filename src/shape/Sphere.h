#ifndef SPHERE_H
#define SPHERE_H

#include "../core/Shape.h"
#include "../core/vec3.h"

class Sphere: public Shape {
    public:
        Sphere() {}
        Sphere(vec3 cen, double r)
            : center(cen), radius(r) {};

        virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        virtual AABB bounding() const;
    public:
        vec3 center;
        double radius;
};

bool Sphere::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
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
            // std::cerr << "Sphere intersected.\n" << std::flush;
            return true;
        }
        temp = (-half_b + root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            // std::cerr << "Sphere intersected.\n" << std::flush;
            return true;
        }
    }
    return false;
}

AABB Sphere::bounding() const {
    return AABB(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
}

std::shared_ptr<Shape> createSphereShape(vec3 cen, double r) {
    return std::make_shared<Sphere>(cen, r);
}

#endif
