#pragma once

#include "../core/Material.h"
#include "../texture/ConstantTexture.h"

namespace mypt {

class Isotropic : public Material {
public:
    Isotropic(vec3 c) : albedo(std::make_shared<ConstantTexture>(c)){}
    Isotropic(std::shared_ptr<Texture> a) : albedo(a) {}

    virtual bool scatter(const Ray& /* r_in */, HitRecord& rec, ScatterRecord& srec) override
    {
        // scattered = Ray(rec.p, random_in_unit_sphere(), r_in.time());
        srec.attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    } 
private:
    std::shared_ptr<Texture> albedo;
};

}