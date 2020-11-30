#include "../core/Transform.h"

int main() {
    Transform t;
    t.pushMatrix();
    t.translate(vec3(1,2,3));
    // t.rotateX(pi/3.0f);

    std::cout << t.getCurrentMatrix() << std::endl;
    std::cout << t.getCurrentInvMatrix() << std::endl;
}