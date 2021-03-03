#pragma once

#include "../core/Material.h"
#include "../texture/ConstantTexture.h"

namespace mypt {

class Isotropic : public Material {
public:
    explicit Isotropic(vec3 c) : albedo(std::make_shared<ConstantTexture>(c)){}
    explicit Isotropic(std::shared_ptr<Texture> a) : albedo(a) {}

    virtual bool scatter(const Ray& /* r_in */, SurfaceInteraction& si) const override
    {
        // scattered = Ray(rec.p, random_in_unit_sphere(), r_in.time());
        si.attenuation = albedo->value(si.uv.x, si.uv.y, si.p);
        return true;
    } 

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Isotropic : {" << std::endl;
        oss << "\tTexture : " << albedo->to_string() << "," << std::endl;
        oss << "}";
        return oss.str();
    }
    
    MatType type() const override { return MatType::Isotropic; }
    
private:
    std::shared_ptr<Texture> albedo;
};

}