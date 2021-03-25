#include "../core/onb.h"

using namespace mypt;

int main() {
    vec3 a = normalize(vec3(1,1,0));
    ONB onb(a);
    std::cout << onb.local(a) << std::endl;

    return 0;
}