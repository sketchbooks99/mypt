#include "../core/Transform.h"

void printTransform(Transform t) {
    std::cout << "mat: \n" << t.getMatrix() << std::endl;
    std::cout << "matInv: \n" << t.getInvMatrix() << std::endl;
}

int main() {
    TransformSystem ts;
    ts.pushMatrix();

    ts.translate(vec3(1,2,3));
    printTransform(ts.getCurrentTransform());
    ts.rotate(pi / 3.0f, vec3(1.0, 1.0, 1.0));
    printTransform(ts.getCurrentTransform());
    ts.scale(3.0f);
    printTransform(ts.getCurrentTransform());

    ts.pushMatrix();
    ts.translate(vec3(3,2,1));
    printTransform(ts.getCurrentTransform());
    ts.rotate(pi / 3.0f, vec3(0.5, 0.5, 0.5));
    printTransform(ts.getCurrentTransform());
    ts.scale(5.0f);
    printTransform(ts.getCurrentTransform());
    ts.popMatrix();

    printTransform(ts.getCurrentTransform());
    ts.popMatrix();

    return 0;
}