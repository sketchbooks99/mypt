#pragma once

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

inline double schlick(double cosine, double ior) {
    auto r0 = (1-ior) / (1+ior);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

class Dielectric final : public Material {
public:
    Dielectric(double ri) : albedo(vec3(1.0f)), ior(ri) {}
    Dielectric(vec3 a, double ri) : albedo(a), ior(ri) {}

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Dielectric : {" << std::endl;
        oss << "\tAlbedo : " << albedo << "," <<  std::endl;
        oss << "\tIndex of Refraction : " << ior << std::endl;
        oss << "}";
        return oss.str();
    }

private:
    vec3 albedo;
    double ior;
};

}
