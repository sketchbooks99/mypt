#pragma once

#include "Ray.h"

namespace mypt {

class Material;
class PDF;

struct HitRecord {
    vec3 p;
    vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    Float t;
    Float u;
    Float v;
    bool front_face;

    inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

struct ScatterRecord {
    Ray specular_ray;
    bool is_specular;
    vec3 attenuation;
    std::shared_ptr<PDF> pdf;
};

enum class MatType {
    Lambertian,
    Dielectric,
    Disney,
    Metal,
    Emitter,
    Isotropic,
    Normal
};

inline std::ostream& operator<<(std::ostream& out, MatType type) {
    switch(type) {
    case MatType::Lambertian:
        return out << "MatType::Lambertian";
        break;
    case MatType::Dielectric:
        return out << "MatType::Dielectric";
        break;
    case MatType::Disney:
        return out << "MatType::Disney";
        break;
    case MatType::Metal:
        return out << "MatType::Metal";
        break;
    case MatType::Emitter:
        return out << "MatType::Emitter";
        break;
    case MatType::Isotropic:
        return out << "MatType::Isotropic";
        break;
    case MatType::Normal:
        return out << "MatType::Normal";
        break;
    }
}

class Material {
public:
    virtual vec3 emitted(
        const Ray& /* r_in */, const HitRecord& /* rec */, Float /* u */, Float /* v */, const vec3& /* p */
    ) const {
        return vec3(0, 0, 0);
    }

    virtual bool scatter (
        const Ray& /* r_in */, HitRecord& /* rec */, ScatterRecord& /* srec */
    ) const {
        return false;
    }

    // Probability distribution function
    virtual Float scattering_pdf (
        const Ray& /* r_in */, const HitRecord& /* rec */, const Ray& /* scattered */
    ) const {
        return 0;
    }

    virtual std::string to_string() const = 0;

    virtual MatType type() const = 0;
};

}

