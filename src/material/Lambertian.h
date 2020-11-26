#pragma once

#include "../core/Material.h"
#include "../core/Texture.h"
#include "../texture/ConstantTexture.h"

struct HitRecord;

class Lambertian final : public Material {
public: 
    Lambertian(vec3 albedo) : albedo(std::make_shared<ConstantTexture>(albedo)) {}
    Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}
    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
    ) const;

private:
    std::shared_ptr<Texture> albedo;
};
