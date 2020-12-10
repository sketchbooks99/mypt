#include "../core/MathUtil.h"
#include "../material/MMAPs.h"

int main() {
    /*
    vec3 n(0, 1, 0);
    for(int i=0; i<100; i++) {
        vec3 in = random_in_hemisphere(n);
        std::cout << "in:             " << in << std::endl;
        std::cout << "retro_transmit: " << retro_transmit(in, n) << std::endl;
        std::cout << "reflect:        " << reflect(in, n) << std::endl;
    }
    */

    vec3 n(0, 1/sqrt(2), 1/sqrt(2));
    n = normalize(n);
    vec3 in(0, 0, -1);
    std::cout << retro_transmit(in, n) << std::endl;
    return 0;
}