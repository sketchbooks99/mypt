#include "../src/core/PBRenderer.h"

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

    // MMAPs
    ts.pushMatrix();
    ts.rotateX(-pi/4.f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-5, -5), vec2(5, 5)),
            std::make_shared<MMAPs>(vec3(1.0f), 0.0f),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    // display
    ts.pushMatrix();
    ts.translate(vec3(0, -5, 0));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-2,-2), vec2(2,2)),
            std::make_shared<Emitter>(vec3(1.0), 5.0f),
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();

    return primitives;
}