#pragma once

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class Metal final : public Material {
public:
    Metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;

private: 
    vec3 albedo;
    double fuzz;
};

}