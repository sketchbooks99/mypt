#pragma once

#include "../core/Material.h"
#include "../core/Texture.h"
#include "../texture/ConstantTexture.h"

namespace mypt {

struct HitRecord;

class Lambertian final : public Material {
public: 
    Lambertian(vec3 albedo) : albedo(std::make_shared<ConstantTexture>(albedo)) {}
    Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}
    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;
    double scattering_pdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) override;
private:
    std::shared_ptr<Texture> albedo;
};

}
