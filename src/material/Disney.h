#pragma once

#include "../core/Material.h"

namespace mypt {

class Disney final : public Material {
public:
    Disney() {}
    Disney(vec3 b, Float ss, Float m, Float sp, Float spT, 
          Float r, Float a, Float sh, Float shT, Float cl, Float clcg)
    : base(b), subsurface(ss), metallic(m), specular(sp), specularTint(spT), 
      roughness(r), anisotropic(a), sheen(sh), sheenTint(shT), clearCoat(cl), clearCoatGloss(clcg) {}

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;
private:
    vec3 base;
    Float subsurface;
    Float metallic;
    Float specular, specularTint;
    Float roughness;
    Float anisotropic;
    Float sheen, sheenTint;
    Float clearCoat, clearCoatGloss;
};

}
