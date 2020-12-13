#pragma once

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

inline double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

class Dielectric final : public Material {
public:
    Dielectric(double ri) : albedo(vec3(1.0f)), ref_idx(ri) {}
    Dielectric(vec3 a, double ri) : albedo(a), ref_idx(ri) {}

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;

private:
    vec3 albedo;
    double ref_idx;
};

}
