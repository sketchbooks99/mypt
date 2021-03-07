#pragma once

#include "ray.h"
#include "texture.h"

namespace mypt {

class Material;
class PDF;

/** MEMO: 
 *  Should SurfaceInteraction store the derivatives on texture coordinates? */
struct SurfaceInteraction {
    vec3 p;
    vec3 n;
    vec2 uv;
    Float t;
    vec3 attenuation;
    Ray scattered;
    bool is_specular;
    bool front_face;
    std::shared_ptr<Material> mat_ptr;
    std::shared_ptr<PDF> pdf_ptr;

    inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        n = front_face ? outward_normal : -outward_normal;
    }
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
    case MatType::Dielectric:
        return out << "MatType::Dielectric";
    case MatType::Disney:
        return out << "MatType::Disney";
    case MatType::Metal:
        return out << "MatType::Metal";
    case MatType::Emitter:
        return out << "MatType::Emitter";
    case MatType::Isotropic:
        return out << "MatType::Isotropic";
    case MatType::Normal:
        return out << "MatType::Normal";
    default:
        return out << "";
    }
}

class Material {
public:
    virtual vec3 emitted(
        const Ray& /* r_in */, const SurfaceInteraction& /* si */
    ) const {
        return vec3(0, 0, 0);
    }

    virtual bool scatter (
        const Ray& /* r_in */, SurfaceInteraction& /* si */
    ) const {
        return false;
    }

    // Probability distribution function
    virtual Float scattering_pdf (
        const Ray& /* r_in */, const SurfaceInteraction& /* si */
    ) const {
        return 0;
    }

    /** TODO: Implementation of Bump mapping. 
     *  Transform normal by using bumpmap texture. */
    // static void bump(const std::shared_ptr<Texture>& bumpmap, SurfaceInteraction& si);

    virtual std::string to_string() const = 0;

    virtual MatType type() const = 0;
};

}

