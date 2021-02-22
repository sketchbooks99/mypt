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
    vec2 uv;
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
    enum class Type { 
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
    virtual Float scattering_pdf (
        const Ray& /* r_in */, const HitRecord& /* rec */, const Ray& /* scattered */
    ) {
        return 0;
    }

    virtual Type type() const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const Material::Type &type) {
    switch(type) {
    case Material::Type::Lambertian:
        return out << "Lambertian";
    case Material::Type::Dielectric:
        return out << "Dielectric";
    case Material::Type::Metal:
        return out << "Metal";
    case Material::Type::Emitter:
        return out << "Emitter";
    case Material::Type::MMAPs:
        return out << "MMAPs";
    case Material::Type::Absorber:
        return out << "Absorber";
    case Material::Type::Isotropic:
        return out << "Isotropic";
    case Material::Type::Normal:
        return out << "Normal";
    default:
        return out << "";
    }
}

}

