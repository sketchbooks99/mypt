#pragma once

#include "../src/core/PBRenderer.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;

    auto earth_texture = std::make_shared<NoiseTexture>(
        1.0f, NoiseTexture::Mode::TURB);
    auto earth_lambert = std::make_shared<Lambertian>(earth_texture);

    // ground
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(0, -1000, 0), 1000),
            earth_lambert
        ));

    // emissive image texture
    auto white_texture = std::make_shared<ConstantTexture>(vec3(1.0f));
    auto emissive = std::make_shared<Emitter>(white_texture, 5.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(1, -5), vec2(11, 5), 7.5,
                Plane::PlaneAxis::YZ),
            emissive
        ));
    
    // bunny 
    auto albedo = vec3(0.8, 0.05, 0.05);
    auto bunny_lambert = std::make_shared<Lambertian>(albedo);
    auto bunny = createTriangleMesh("data/model/bunny.obj", vec3(), 1.0f, vec3(1,1,1), true);
    for(auto &triangle : bunny) {
        auto transformed_triangle = std::make_shared<TransformPrimitive>(
            std::make_shared<ShapePrimitive>(
                triangle, bunny_lambert));
        transformed_triangle->scale(40.0f);
        // transformed_triangle->rotate(3*pi, vec3(1,2,3));
        // transformed_triangle->translate(vec3(0, 2, 0));
        // transformed_triangle->rotate_x(pi/3.0f);
        primitives.emplace_back(transformed_triangle);
    }   

    return primitives;
}