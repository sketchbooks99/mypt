#include "../src/core/PBRenderer.h"

void printTransform(Transform t) {
    std::cout << t.getMatrix() << std::endl;
    std::cout << t.getInvMatrix() << std::endl;
}

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;
    TransformSystem ts;


    // right side
    ts.pushMatrix();
    ts.translate(vec3(10.0f, 0.0f, 0.0f));
    ts.rotateZ(pi/2.0f);
    ts.scale(10.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-1, -1), vec2(1, 1), 0.0,
                Plane::PlaneAxis::XZ),
            std::make_shared<Lambertian>(vec3(0.05, 0.8, 0.05)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // left 
    ts.pushMatrix();
    ts.translate(vec3(-10.0f, 0.0f, 0.0f));
    ts.rotateZ(pi/2.0f);
    ts.scale(10.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-1, -1), vec2(1, 1), 0.0,
                Plane::PlaneAxis::XZ),
            std::make_shared<Lambertian>(vec3(0.8, 0.05, 0.05)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // top
    ts.pushMatrix();
    ts.translate(vec3(0.0, 10.0f, 0.0f));
    ts.scale(10.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-1, -1), vec2(1, 1), 0.0,
                Plane::PlaneAxis::XZ),
            std::make_shared<Lambertian>(vec3(0.8)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // bottom
    ts.pushMatrix();
    ts.translate(vec3(0.0f, -10.0f, 0.0f));
    ts.scale(10.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-1, -1), vec2(1, 1), 0.0,
                Plane::PlaneAxis::XZ),
            std::make_shared<Lambertian>(vec3(0.8)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // back
    ts.pushMatrix();
    ts.translate(vec3(0.0f, 0.0f, 100.0f));
    ts.rotateX(pi/2.0f);
    ts.scale(10.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-1, -1), vec2(1, 1), 0.0,
                Plane::PlaneAxis::XZ),
            std::make_shared<Lambertian>(vec3(0.8)),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // light
    ts.pushMatrix();
    ts.translate(vec3(0.0, -5.0f, 0.0));
    ts.scale(5.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-1, -1), vec2(1, 1), 0.0,
                Plane::PlaneAxis::XZ),
            std::make_shared<Emitter>(vec3(1.0f, 1.0f, 0.0f), 10.0f),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    return primitives;
}