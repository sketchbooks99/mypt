#pragma once

#include "../core/Material.h"
#include "../core/Texture.h"
#include "../texture/ConstantTexture.h"

namespace mypt {

struct HitRecord;

class Emitter final : public Material {
public:
    Emitter(std::shared_ptr<Texture> a, float intensity=1.0f) 
     : albedo(a), intensity(intensity) {};
    Emitter(vec3 a, float intensity=1.0f)
     : albedo(std::make_shared<ConstantTexture>(a)), intensity(intensity) {};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;
    vec3 emitted(const Ray& r_in, const HitRecord& rec) override;

    Type type() const override { return Type::Emitter; }
    
private:
    std::shared_ptr<Texture> albedo;
    float intensity;
};

}