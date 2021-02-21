#pragma once

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class MMAPs final : public Material {
public:
    MMAPs(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;

    MatType type() const override { return MatType::MMAPs; }
private:
    vec3 albedo;
    double fuzz;
};

}