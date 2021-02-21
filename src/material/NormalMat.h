#pragma once 

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class NormalMat final : public Material {
public:
    NormalMat(bool is_emit=false) : is_emit(is_emit){};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;
    double scattering_pdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) override;
    vec3 emitted(const Ray& r_in, const HitRecord& rec) override;

    MatType type() const override { return MatType::Normal; }

private:
    bool is_emit;
};

}