#pragma once

#include "../core/material.h"
#include "../texture/constant.h"

namespace mypt {

class Disney final : public Material {
public:
    explicit Disney() {}

    Disney(vec3 b, Float ss, Float m, Float sp, Float spT, 
          Float r, Float a, Float sh, Float shT, Float cl, Float clcg)
    : base(std::make_shared<ConstantTexture>(b)), subsurface(ss), metallic(m), specular(sp), specularTint(spT), 
      roughness(r), anisotropic(a), sheen(sh), sheenTint(shT), clearCoat(cl), clearCoatGloss(clcg) {}

    Disney(std::shared_ptr<Texture> b, Float ss, Float m, Float sp, Float spT, 
          Float r, Float a, Float sh, Float shT, Float cl, Float clcg)
    : base(b), subsurface(ss), metallic(m), specular(sp), specularTint(spT), 
      roughness(r), anisotropic(a), sheen(sh), sheenTint(shT), clearCoat(cl), clearCoatGloss(clcg) {}

    bool scatter(const Ray& r_in, SurfaceInteraction& si) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Disney BSDF : {" << std::endl;
        oss << "\tBase : " << base->to_string() << "," << std::endl;
        oss << "\tSubSurface : " << subsurface << "," << std::endl; 
        oss << "\tMetallic : " << metallic << "," << std::endl; 
        oss << "\tSpecular : " << specular << "," << std::endl; 
        oss << "\tSpecularTint : " << specularTint << "," << std::endl; 
        oss << "\tRoughness : " << roughness << "," << std::endl; 
        oss << "\tAnisotropic : " << anisotropic << "," << std::endl; 
        oss << "\tSheen : " << sheen << "," << std::endl;
        oss << "\tSheenTint : " << sheenTint << "," << std::endl;
        oss << "\tClearCoat : " << clearCoat << "," << std::endl;
        oss << "\tClearCoatGloss : " << clearCoatGloss << "," << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    MatType type() const override { return MatType::Disney; }
private:
    std::shared_ptr<Texture> base;
    Float subsurface;
    Float metallic;
    Float specular, specularTint;
    Float roughness;
    Float anisotropic;
    Float sheen, sheenTint;
    Float clearCoat, clearCoatGloss;
};

}
