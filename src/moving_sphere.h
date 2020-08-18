#ifndef Moving_sphere_h
#define Moving_sphere_h

#include "vec3.h"
#include "Hittable.h"

class Moving_sphere : public Hittable {
    public:
        Moving_sphere() {}
        Moving_sphere(
            vec3 cen0, vec3 cen1, double t0, double t1, double r, shared_ptr<Material> m)
            : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m)
        {};

        virtual bool hit(const Ray& r, double tmin, double tmax, Hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, AABB& output_box) const;

        vec3 center(double time) const;

    public:
        vec3 center0, center1;
        double time0, time1;
        double radius;
        shared_ptr<Material> mat_ptr;
};

vec3 Moving_sphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool Moving_sphere::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const {
    vec3 oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;

    if(discriminant > 0) {
        auto root = sqrt(discriminant);

        auto temp = (-half_b - root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-half_b + root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

bool Moving_sphere::bounding_box(double t0, double t1, AABB& output_box) const {
    AABB box0(
        center(t0) - vec3(radius, radius, radius),
        center(t0) + vec3(radius, radius, radius));
    AABB box1(
        center(t1) - vec3(radius, radius, radius),
        center(t1) + vec3(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}

#endif