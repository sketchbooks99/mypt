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
    Dielectric(double ri, bool is_normal=false)
    : albedo(vec3(1.0f)), ref_idx(ri), is_normal(is_normal) {}
    Dielectric(vec3 a, double ri, bool is_normal=false)
    : albedo(a), ref_idx(ri), is_normal(is_normal) {}

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;

private:
    vec3 albedo;
    double ref_idx;
    bool is_normal;
};

}
