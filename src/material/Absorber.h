#pragma once

#include "../core/Image.h"
#include "../core/Material.h"

namespace mypt {

struct HitRecord;

template <typename PixelType>
class Absorber final : public Material {
public:
    Absorber(std::shared_ptr<Image<PixelType>> image, const std::string& filename)
    : image(image), filename(filename) {};
    ~Absorber();
    bool scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& srec) override;

    std::shared_ptr<Image<PixelType>> getImagePtr() { return image; }
    Image<PixelType> getImage() { return *image; }

    MatType type() const override { return MatType::Absorber; }
private:
    std::shared_ptr<Image<PixelType>> image;
    std::string filename;
};

}