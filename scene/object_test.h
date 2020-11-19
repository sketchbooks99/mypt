#pragma once

#include "../src/core/PBRenderer.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;

    auto checker = std::make_shared<CheckerTexture>(
        std::make_shared<ConstantTexture>(vec3(0.2, 0.3, 0.1)),
        std::make_shared<ConstantTexture>(vec3(0.9, 0.9, 0.9))
    );
    auto checker_lambert = std::make_shared<Lambertian>(checker);

    auto ground_lambert = std::make_shared<Lambertian>(1.0f);

    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(0, -1000, 0), 1000),
            checker_lambert
        ));

    for(int a = -11; a <= 11; a++) {
        for(int b = -11; b <= 11; b++) {
            vec3 albedo = vec3::random() * vec3::random() * 1.5f;
            // vec3 albedo = vec3(1.0f);
            vec3 center(a * random_double() * 2, 0.5, b * random_double() * 2);
            primitives.emplace_back(
                std::make_shared<ShapePrimitive>(
                    createSphereShape(center, random_double() * 0.5),
                    std::make_shared<Lambertian>(albedo)
                ));
        }
    }
    
    auto bunny = createTriangleMesh("model/bunny.obj", vec3(0.0, 1.0, 0.0), 20.0, vec3(1, 1, 1), true);
    auto bunny_diffuse = std::make_shared<Lambertian>(vec3(0.8, 0.05, 0.05));
    for (auto &triangle : bunny){
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(
                triangle, bunny_diffuse
            ));
    }
    
    return primitives;
}