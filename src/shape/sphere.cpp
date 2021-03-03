#include "sphere.h"
#include "../core/onb.h"

namespace mypt {

/// \private function -------------------------------------------------
vec2 Sphere::getUV(const vec3& p) const {
    vec3 tmp = p / radius;
    auto phi = atan2(tmp.z, tmp.x);
    auto theta = asin(tmp.y);
    auto u = 1.0 - (phi + pi) / (2.0*pi);
    auto v = (theta + pi/2.0) / pi;
    return vec2(u, v);
}

/// \public function --------------------------------------------------
bool Sphere::intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const {
    // vector from origin to center
    vec3 oc = r.origin();
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    si.t = root;
    si.p = r.at(si.t);
    vec3 outward_normal = si.p / radius;
    si.n = outward_normal;

    return true;
}

// -----------------------------------------------------------------------
Float Sphere::pdf_value(const vec3& o, const vec3& v) const {
    SurfaceInteraction si;
    if(!this->intersect(Ray(o, v), eps, infinity, si)) 
        return 0;
    auto cos_theta_max = sqrt(1 - radius*radius/o.length_squared());
    auto solid_angle = 2*pi*(1-cos_theta_max);

    return 1 / solid_angle;
}
        
// -----------------------------------------------------------------------
vec3 Sphere::random(const vec3& o) const {
    vec3 direction = -o;
    auto distance_squared = direction.length_squared();
    ONB onb;
    onb.build_from_w(direction);
    return onb.local(random_to_sphere(radius, distance_squared));
}

// -----------------------------------------------------------------------
AABB Sphere::bounding() const {
    return AABB(
        vec3(-radius, -radius, -radius),
        vec3(radius, radius, radius));
}

std::shared_ptr<Shape> createSphereShape(Float r) {
    return std::make_shared<Sphere>(r);
}

}