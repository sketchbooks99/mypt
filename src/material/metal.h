#pragma once

#include "../core/material.h"

namespace mypt {

struct HitRecord;

class Metal final : public Material {
public:
    explicit Metal(const vec3& a, Float f) : albedo(a), fuzz(f < 1 ? f : 1) {};

    bool scatter(const Ray& r_in, SurfaceInteraction& si) const override;
    Float scattering_pdf(const Ray& /* r_in */, const SurfaceInteraction& /* si */) const override {
        return 1.0f;
    }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Metal : {" << std::endl;
        oss << "\tAlbedo : " << albedo << "," << std::endl;
        oss << "\tFuzz : " << fuzz << std::endl;
        oss << "}";
        return oss.str();
    }

    MatType type() const override { return MatType::Metal; }

private: 
    vec3 albedo;
    Float fuzz;
};

}