#pragma once

#include "../core/Material.h"
#include "../core/Texture.h"

struct HitRecord;

class Emitter : public Material {
public:
    Emitter(std::shared_ptr<Texture> a, float intensity=1.0f) 
    : albedo(a), intensity(intensity) {}
    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, vec3 &attenuation, Ray& scattered
    ) const {
        return false;
    }

    virtual vec3 emitted(double u, double v, const vec3& p) const {
        return albedo->value(u, v, p) * intensity;
    }
    
private:
    std::shared_ptr<Texture> albedo;
    float intensity;
};