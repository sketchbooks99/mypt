#pragma once

#include "../src/core/PBRenderer.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;

    auto earth_texture = std::make_shared<ImageTexture>("data/image/earth.jpg");
    auto earth_lambert = std::make_shared<Lambertian>(vec3(1.0f));

    // ground
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-100, -100), vec2(100, 100), -5.0f,
                Plane::PlaneAxis::XZ),
            earth_lambert
        ));

    // emissive image texture
    auto white_texture = std::make_shared<ConstantTexture>(vec3(1.0f));
    auto emissive = std::make_shared<Emitter>(white_texture, 5.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(1, 1), vec2(11, 11), 5.0,
                Plane::PlaneAxis::YZ),
            emissive
        ));
    
    // bunny 
    auto albedo = vec3(0.8, 0.05, 0.05);
    auto bunny_lambert = std::make_shared<Lambertian>(albedo);
    auto bunny = createTriangleMesh("data/model/bunny.obj", vec3(0.0, 1.0f, 0.0), 40.0, vec3(1,1,1), true);
    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(
                triangle, bunny_lambert
            ));
    }   

    return primitives;
}