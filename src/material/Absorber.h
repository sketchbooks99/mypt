#pragma once

#include "../core/Image.h"
#include "../core/Material.h"

namespace mypt {

struct HitRecord;

class Absorber final : public Material {
public:
    Absorber(int width, int height) : image(Image<RGBA>(width, height)) {}
    // ~Absorber();
    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;
private:
    Image<RGBA> image;
};

}