#pragma once 

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class NormalMat final : public Material {
public:
    NormalMat(){};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;
    double scattering_pdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) override;
};

}