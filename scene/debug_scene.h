#pragma once 

#include "../src/core/mypt.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;

    auto checker = std::make_shared<CheckerTexture>(
        std::make_shared<ConstantTexture>(vec3(0.2, 0.3, 0.1)),
        std::make_shared<ConstantTexture>(vec3(0.8, 0.8, 0.8))
    );
    auto checker_lambert = std::make_shared<Lambertian>(checker);

    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(0, -1000, 0), 1000),
            checker_lambert
        ));
    
    auto albedo = std::make_shared<Lambertian>(vec3(0.2, 0.8, 0.8));
    // auto dielectric = std::make_shared<Dielectric>(1.52);
    auto albedo2 = std::make_shared<Lambertian>(vec3(0.8, 0.05, 0.05));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(-2.5, 5, 0), 5),
            albedo
        ));
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(2.5, 5, 0), 5),
            albedo2
        ));
    
    return primitives;
}