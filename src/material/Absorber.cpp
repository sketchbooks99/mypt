#include "Absorber.h"

namespace mypt {

// Absorber::~Absorber() {
//     std::string filename = "inv_result.png";
//     image.write(filename, split(filename, '.').back());
// }

bool Absorber::scatter(const Ray& r_in, HitRecord& rec, ScatterRecord& /* srec */) {
    // Absorb propagated color by ray
    auto x = static_cast<int>(image.getWidth() * rec.u);
    auto y = static_cast<int>(image.getHeight() * rec.v);
    image.set(x, y, r_in.color());
    std::cout << "hoge" << std::endl;
    return false;
}

}