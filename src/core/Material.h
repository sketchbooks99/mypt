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

/**
 * NOTE:
 *  Disable const function to modify member variables in functions.
 *  This is especially for `Absorber`.
 */

class Material {
public:
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
};

}

