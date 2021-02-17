#pragma once

#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class Metal final : public Material {
public:
    Metal(const vec3& a, Float f) : albedo(a), fuzz(f < 1 ? f : 1) {};

    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) const override;

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Metal : {" << std::endl;
        oss << "\tAlbedo : " << albedo << "," << std::endl;
        oss << "\tFuzz : " << fuzz << std::endl;
        oss << "}";
        return oss.str();
    }

private: 
    vec3 albedo;
    Float fuzz;
};

}