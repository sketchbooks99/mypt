#pragma once 

#include "../core/Material.h"

struct HitRecord;

class NormalMat final : public Material {
public:
    NormalMat(){};

    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered, double& pdf) const override;
};