#include "../src/core/mypt.h"

using namespace mypt;

void printTransform(Transform t) {
    std::cout << t.getMatrix() << std::endl;
    std::cout << t.getInvMatrix() << std::endl;
}

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;
    TransformSystem ts;

    // right side
    ts.pushMatrix();
    ts.translate(vec3(10, 0, 0));
    ts.rotateZ(pi/2.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-10, -10), vec2(10, 10)),
            std::make_shared<Lambertian>(vec3(0.8, 0.05, 0.05)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // left 
    ts.pushMatrix();
    ts.translate(vec3(-10, 0, 0));
    ts.rotateZ(pi/2.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-10, -10), vec2(10, 10)),
            std::make_shared<Lambertian>(vec3(0.05, 0.08, 0.05)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // top
    ts.pushMatrix();
    ts.translate(vec3(0, 10, 0));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-10, -10), vec2(10, 10)),
            std::make_shared<Lambertian>(vec3(0.8)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // bottom
    ts.pushMatrix();
    ts.translate(vec3(0, -10, 0));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-10, -10), vec2(10, 10)),
            std::make_shared<Lambertian>(vec3(0.8)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // back
    ts.pushMatrix();
    ts.translate(vec3(0, 0, 10));
    ts.rotateX(pi/2.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-10, -10), vec2(10, 10)),
            std::make_shared<Lambertian>(vec3(0.8)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // light
    ts.pushMatrix();
    ts.translate(vec3(0, 9.8f, 0));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-5, -5), vec2(5, 5)),
            std::make_shared<Emitter>(vec3(0.9f, 0.7f, 0.3f), 10.0f),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    ts.pushMatrix();
    ts.translate(vec3(-5,-6,5));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(3.0),
            std::make_shared<Lambertian>(vec3(1.0, 1.0, 1.0)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    ts.pushMatrix();
    ts.translate(vec3(5,-5,5));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(4.0),
            std::make_shared<Lambertian>(vec3(1.0, 1.0, 1.0)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    return primitives;
}