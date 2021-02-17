#include "MovingSphere.h"

namespace mypt {

vec3 MovingSphere::center(Float time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MovingSphere::intersect(const Ray& r, Float t_min, Float t_max, HitRecord& rec) const {
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
            return true;
        }

        temp = (-half_b + root) / a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            return true;
        }
    }

    return false;
}

AABB MovingSphere::bounding() const {
    AABB box0(
        center(time0) - vec3(radius, radius, radius),
        center(time0) + vec3(radius, radius, radius));
    AABB box1(
        center(time1) - vec3(radius, radius, radius),
        center(time1) + vec3(radius, radius, radius));
    return surrounding(box0, box1);
}

std::shared_ptr<Shape> createMovingSphere(vec3 cen0, vec3 cen1, Float t0, Float t1, Float r) {
    return std::make_shared<MovingSphere>(cen0, cen1, t0, t1, r);
}

}