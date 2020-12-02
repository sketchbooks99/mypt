#include "../core/Transform.h"

void printTransform(Transform t) {
    std::cout << t.getCurrentMatrix() << std::endl;
    std::cout << t.getCurrentInvMatrix() << std::endl;
}

int main() {
    Transform t;
    t.pushMatrix();

    t.translate(vec3(1,2,3));
    printTransform(t);
    t.rotate(pi / 3.0f, vec3(1.0, 1.0, 1.0));
    printTransform(t);
    t.scale(3.0f);
    printTransform(t);

    t.pushMatrix();
    t.translate(vec3(3,2,1));
    printTransform(t);
    t.rotate(pi / 3.0f, vec3(0.5, 0.5, 0.5));
    printTransform(t);
    t.scale(5.0f);
    printTransform(t);
    t.popMatrix();

    printTransform(t);
    t.popMatrix();

    return 0;
}