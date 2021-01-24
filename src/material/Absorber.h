#pragma once

#include "../core/Image.h"
#include "../core/Material.h"

namespace mypt {

struct HitRecord;

template <typename PixelType>
class Absorber final : public Material {
public:
    Absorber(Image<PixelType> image, std::string filename)
    : image(std::move(image)), filename(filename), Material(MatType::ABSORBER) {};
    ~Absorber();
    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;

    Image<PixelType> getImage() { return image; }
private:
    Image<PixelType> image;
    std::string filename;
};

}