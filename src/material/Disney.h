#pragma once

#include "../core/Material.h"

namespace mypt {

class Disney final : public Material {
public:
    Disney() {}
    Disney(vec3 b, float ss, float m, float sp, float spT, 
          float r, float a, float sh, float shT, float cl, float clcg)
    : base(b), subsurface(ss), metallic(m), specular(sp), specularTint(spT), 
      roughness(r), anisotropic(a), sheen(sh), sheenTint(shT), clearCoat(cl), clearCoatGloss(clcg) {}

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;
private:
    vec3 base;
    float subsurface;
    float metallic;
    float specular, specularTint;
    float roughness;
    float anisotropic;
    float sheen, sheenTint;
    float clearCoat, clearCoatGloss;
};

}
