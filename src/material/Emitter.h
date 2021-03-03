#pragma once

#include "../core/Material.h"
#include "../core/Texture.h"
#include "../texture/ConstantTexture.h"

namespace mypt {

struct HitRecord;

class Emitter final : public Material {
public:
    explicit Emitter(std::shared_ptr<Texture> a, float intensity=1.0f) 
     : albedo(a), intensity(intensity) {};
    explicit Emitter(vec3 a, float intensity=1.0f)
     : albedo(std::make_shared<ConstantTexture>(a)), intensity(intensity) {};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;
    vec3 emitted(const Ray& r_in, const HitRecord& rec, Float u, Float v, const vec3& p) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Emitter : {" << std::endl;
        oss << "\tTexture : " << albedo->to_string() << "," << std::endl;
        oss << "\tIntensity : " << intensity << std::endl;
        oss << "}";
        return oss.str();
    }

    MatType type() const override { return MatType::Emitter; }
    
private:
    std::shared_ptr<Texture> albedo;
    float intensity;
};

}