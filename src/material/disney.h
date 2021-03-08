#pragma once

#include "../core/material.h"
#include "../texture/constant.h"

namespace mypt {

/** 
 * @param
 * - base : base color on the surface
 * - subsurface : Control a behaivior of diffuse BRDF between lambert(0) and subsurface scattering(1)
 * - metallic : 0 ... dielectric. 1 ... conductor
 * - specular : Specular reflectance of non-metallic
 * - specularTint : Color of specular reflectance. 1 ... base color (but colorless at grazing angle)
 * - roughness : Roughness of surface. This affects both of diffuse and specular reflectance.
 * - anisotropic : Anistropic amount of specular highlight.
 * - sheen : Additional component at grazing angle (mainly for cloth).
 * - sheenTint : A value how the sheen color bring closer to base color.
 * - clearcoat : Strength of second specular lobe.
 * - clearcoatGloss : Control glossy of clearcoat.
 */

class Disney final : public Material {
public:
    explicit Disney() {}

    Disney(vec3 b, Float ss, Float m, Float sp, Float spT, 
          Float r, Float a, Float sh, Float shT, Float cl, Float clcg)
    : m_base(std::make_shared<ConstantTexture>(b)), m_subsurface(ss), m_metallic(m), m_specular(sp), m_specularTint(spT), 
      m_roughness(r), m_anisotropic(a), m_sheen(sh), m_sheenTint(shT), m_clearCoat(cl), m_clearCoatGloss(clcg) {}

    Disney(std::shared_ptr<Texture> b, Float ss, Float m, Float sp, Float spT, 
          Float r, Float a, Float sh, Float shT, Float cl, Float clcg)
    : m_base(b), m_subsurface(ss), m_metallic(m), m_specular(sp), m_specularTint(spT), 
      m_roughness(r), m_anisotropic(a), m_sheen(sh), m_sheenTint(shT), m_clearCoat(cl), m_clearCoatGloss(clcg) {}

    bool scatter(const Ray& r_in, SurfaceInteraction& si) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Disney BSDF : {" << std::endl;
        oss << "\tBase : " << m_base->to_string() << "," << std::endl;
        oss << "\tSubsurface : " << m_subsurface << "," << std::endl; 
        oss << "\tMetallic : " << m_metallic << "," << std::endl; 
        oss << "\tSpecular : " << m_specular << "," << std::endl; 
        oss << "\tSpecularTint : " << m_specularTint << "," << std::endl; 
        oss << "\tRoughness : " << m_roughness << "," << std::endl; 
        oss << "\tAnisotropic : " << m_anisotropic << "," << std::endl; 
        oss << "\tSheen : " << m_sheen << "," << std::endl;
        oss << "\tSheenTint : " << m_sheenTint << "," << std::endl;
        oss << "\tClearCoat : " << m_clearCoat << "," << std::endl;
        oss << "\tClearCoatGloss : " << m_clearCoatGloss << "," << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    MatType type() const override { return MatType::Disney; }
private:
    std::shared_ptr<Texture> m_base;
    Float m_subsurface;
    Float m_metallic;
    Float m_specular, m_specularTint;
    Float m_roughness;
    Float m_anisotropic;
    Float m_sheen, m_sheenTint;
    Float m_clearCoat, m_clearCoatGloss;
};

}
