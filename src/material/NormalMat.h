#pragma once 

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class NormalMat final : public Material {
public:
    NormalMat(){};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;
    Float scattering_pdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "NormalMat";
        return oss.str();
    }

    MatType type() const override { return MatType::Normal; }
};

}