#pragma once

#include "../src/core/PBRenderer.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;
    TransformSystem ts;
    
    auto earth_texture = std::make_shared<NoiseTexture>(
        1.0f, NoiseTexture::Mode::TURB);
    auto earth_lambert = std::make_shared<Lambertian>(earth_texture);

    // ground
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(0, -1000, 0), 1000),
            earth_lambert,
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    
    ts.pushMatrix();
    ts.translate(vec3(0.0f, 15.0, 0.0f));
    ts.scale(2.0f);
    // emissive image texture
    auto white_texture = std::make_shared<ConstantTexture>(vec3(1.0f));
    auto emissive = std::make_shared<Emitter>(white_texture, 5.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-5, -5), vec2(5, 5), 0.0,
                Plane::PlaneAxis::XZ),
            emissive,
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    ts.popMatrix();
    
    
    ts.pushMatrix();
    ts.translate(vec3(-5, 5, 0));
    ts.rotate(pi/3.0f, vec3(1,2,3));
    ts.scale(50.0f);

    auto albedo = vec3(0.8, 0.05, 0.05);
    auto bunny_lambert = std::make_shared<Lambertian>(albedo);
    auto bunny = createTriangleMesh("data/model/bunny.obj", vec3(0.0f), 1.0f, vec3(1,1,1), true);
    auto bunny_transform = std::make_shared<Transform>(ts.getCurrentTransform());

    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(triangle, bunny_lambert, bunny_transform));
    }

    ts.popMatrix();

    ts.pushMatrix();
    ts.translate(vec3(5, 5, 0));
    ts.rotate(-pi/3.0f, vec3(1,2,3));
    ts.scale(50.0f);

    albedo = vec3(0.05, 0.8, 0.05);
    bunny_lambert = std::make_shared<Lambertian>(albedo);
    bunny = createTriangleMesh("data/model/bunny.obj", vec3(0.0f), 1.0f, vec3(1,1,1), true);
    bunny_transform = std::make_shared<Transform>(ts.getCurrentTransform());

    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(triangle, bunny_lambert, bunny_transform));
    }

    ts.popMatrix();

    return primitives;
}