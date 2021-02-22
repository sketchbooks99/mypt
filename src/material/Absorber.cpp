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
    auto x = static_cast<int>(image->getWidth() * rec.uv.x);
    auto y = static_cast<int>(image->getHeight() * rec.uv.y);
    image->set(x, y, r_in.color());
    std::cout << "p:" << rec.p << ",dir:" << r_in.direction() << std::endl;
    return false;
}
template bool Absorber<RGBA>::scatter(const Ray&, HitRecord&, ScatterRecord&);

}