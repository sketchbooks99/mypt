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
            ts.getCurrentTransformPtr()
        ));

    // emissive image texture
    auto white_texture = std::make_shared<ConstantTexture>(vec3(1.0f));
    auto emissive = std::make_shared<Emitter>(white_texture, 5.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(1, -5), vec2(11, 5), 7.5,
                Plane::PlaneAxis::YZ),
            emissive,
            ts.getCurrentTransformPtr()
        ));
    
    // bunny 
    auto albedo = vec3(0.8, 0.05, 0.05);
    auto bunny_lambert = std::make_shared<Lambertian>(albedo);
    auto bunny = createTriangleMesh("data/model/bunny.obj", vec3(), 1.0f, vec3(1,1,1), true);
    ts.pushMatrix();
    // ts.translate(vec3(1,3,1));
    ts.scale(40.0f);
    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(triangle, bunny_lambert, ts.getCurrentTransformPtr()));
    }   
    ts.popMatrix();

    return primitives;
}