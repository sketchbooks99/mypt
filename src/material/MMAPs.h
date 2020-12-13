#pragma once

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class MMAPs final : public Material {
public:
    MMAPs(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;
private:
    vec3 albedo;
    double fuzz;
};

inline vec3 retro_transmit(const vec3& v, const vec3& n) {
    return - v + 2*dot(v, n) * n;
}

}