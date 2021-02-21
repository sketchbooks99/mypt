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
    Ray scattered;
    bool is_specular;
    vec3 attenuation;
    std::shared_ptr<PDF> pdf;
};

// Abstract class 

/** NOTE:
 *  Disable const directive of member functions to modify member variables.
 *  This is especially for `Absorber`. */

enum class MatType {
    None,
    Lambertian,
    Dielectric,
    Metal,
    Emitter,
    MMAPs,
    Absorber,
    Isotropic,
    Normal
};

inline std::ostream& operator<<(std::ostream& out, const MatType &mt) {
    switch(mt) {
    case MatType::Lambertian:
        return out << "Lambertian";
    case MatType::Dielectric:
        return out << "Dielectric";
    case MatType::Metal:
        return out << "Metal";
    case MatType::Emitter:
        return out << "Emitter";
    case MatType::MMAPs:
        return out << "MMAPs";
    case MatType::Absorber:
        return out << "Absorber";
    case MatType::Isotropic:
        return out << "Isotropic";
    case MatType::Normal:
        return out << "Normal";
    default:
        return out << "";
    }
}

inline void stream_intersection(const Ray& r, const HitRecord& rec, const ScatterRecord& srec) {
    std::cout << "time:" << rec.t;
    std::cout << ",p:" << rec.p;
    std::cout << ",origin:" << r.origin();
    std::cout << ",in:" << r.direction();
    std::cout << ",out:" << srec.scattered.direction();
    std::cout << ",normal:" << rec.normal << std::endl;
}

class Material {
public:
    Material() {}
    virtual vec3 emitted(
        const Ray& /* r_in */, const HitRecord& /* rec */
    ) {
        return vec3(0, 0, 0);
    }

    virtual bool scatter (
        const Ray& /* r_in */, HitRecord& /* rec */, ScatterRecord& /* srec */
    ) {
        return false;
    }

    // Probability distribution function
    virtual double scattering_pdf (
        const Ray& /* r_in */, const HitRecord& /* rec */, const Ray& /* scattered */
    ) {
        return 0;
    }

    virtual MatType type() const = 0;
};

}

