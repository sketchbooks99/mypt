#pragma once

#include "../core/Material.h"

struct HitRecord;

class Metal final : public Material {
public:
    Metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {};

    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered, double& pdf) const override;

private: 
    vec3 albedo;
    double fuzz;
};