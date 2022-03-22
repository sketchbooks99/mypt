#pragma once

#include "ray.h"
#include "texture.h"

namespace mypt {

class Material;
class PDF;

/** MEMO: 
 *  Should SurfaceInteraction store the derivatives on texture coordinates? */
struct SurfaceInteraction {
    // Surface point
    vec3 p;

    // Surface normal
    vec3 n;

    // Texture coordinate
    vec2 uv;

    // Ray time
    Float t;

    // Surface albedo
    /// @todo : must be attenuation -> @c albedo
    vec3 attenuation;

    // Partial derivative on texture coordinate.
    vec3 dpdu;
    vec3 dpdv;

    // Scatterd ray information
    /// @note It can be change from Ray to vec3 struct, 
    ///       because the ray origin is defined as @c p
    Ray scattered;

    // Flag to determine if the surface is specular or not
    bool is_specular;

    // Flag to determine if the surface is front face or not
    bool front_face;

    // Material pointer associated with the surface
    std::shared_ptr<Material> mat_ptr;

    // PDF pointer associated with the material
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

