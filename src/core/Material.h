#pragma once

#include "Ray.h"

namespace mypt {

class Material;
class PDF;

struct HitRecord {
    vec3 p;
    vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    double t;
    double u;
    double v;
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

// Abstract class 

/**
 * NOTE:
 *  Disable const function to modify member variables in functions.
 *  This is especially for `Absorber`.
 */

enum MatType {
    LAMBERTIAN,
    DIELECTRIC,
    METAL,
    EMITTER,
    MMAPS,
    ABSORBER,
    ISOTROPIC,
    NORMAL
};

inline std::ostream& operator<<(std::ostream& out, const MatType &mt) {
    switch(mt) {
    case MatType::LAMBERTIAN:
        return out << "LAMBERTIAN" << std::endl;
        break;
    case MatType::DIELECTRIC:
        return out << "DIELECTRIC" << std::endl;
        break;
    case MatType::METAL:
        return out << "METAL" << std::endl;
        break;
    case MatType::EMITTER:
        return out << "EMITTER" << std::endl;
        break;
    case MatType::MMAPS:
        return out << "MMAPS" << std::endl;
        break;
    case MatType::ABSORBER:
        return out << "ABSORBER" << std::endl;
        break;
    case MatType::ISOTROPIC:
        return out << "ISOTROPIC" << std::endl;
        break;
    case MatType::NORMAL:
        return out << "NORMAL" << std::endl;
        break;
    default:
        break;
    }
}

class Material {
public:
    Material(MatType mattype=MatType::LAMBERTIAN) : mattype(mattype) {}
    virtual vec3 emitted(
        const Ray& /* r_in */, const HitRecord& /* rec */, double /* u */, double /* v */, const vec3& /* p */
    ) const {
        return vec3(0, 0, 0);
    }

    virtual bool scatter (
        const Ray& /* r_in */, HitRecord& /* rec */, ScatterRecord& /* srec */
    ) const {
        return false;
    }

    // Probability distribution function
    virtual double scattering_pdf (
        const Ray& /* r_in */, const HitRecord& /* rec */, const Ray& /* scattered */
    ) const {
        return 0;
    }

    MatType get_type() const { return mattype; }

private:
    MatType mattype;
};

}

