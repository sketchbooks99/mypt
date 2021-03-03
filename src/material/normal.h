#pragma once 

#include "../core/material.h"

namespace mypt {

struct HitRecord;

class NormalMat final : public Material {
public:
    explicit NormalMat(){};

    bool scatter(const Ray& r_in, SurfaceInteraction& si) const override;
    Float scattering_pdf(const Ray& r_in, const SurfaceInteraction& si) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "NormalMat";
        return oss.str();
    }

    MatType type() const override { return MatType::Normal; }
};

}