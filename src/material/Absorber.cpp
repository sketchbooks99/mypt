#include "Absorber.h"

namespace mypt {

template <typename PixelType>
Absorber<PixelType>::~Absorber() {
    std::cout << "Write " << filename << std::endl;
    image->write(filename, split(filename, '.').back());
}
template Absorber<RGBA>::~Absorber();

template <typename PixelType>
bool Absorber<PixelType>::scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& /* srec */) {
    // Absorb propagated color by ray
    auto x = static_cast<int>(image->getWidth() * rec.u);
    auto y = static_cast<int>(image->getHeight() * rec.v);
    image->set(x, y, r_in.color());
    return false;
}
template bool Absorber<RGBA>::scatter(const Ray&, HitRecord&, ScatterRecord&);

}