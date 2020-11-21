#pragma once

#include "../src/core/PBRenderer.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;

    auto checker = std::make_shared<CheckerTexture>(
        std::make_shared<ConstantTexture>(vec3(0.2, 0.3, 0.1)),
        std::make_shared<ConstantTexture>(vec3(0.9, 0.9, 0.9)),
        100
    );
    auto checker_lambert = std::make_shared<Lambertian>(checker);

    auto image_texture = std::make_shared<ImageTexture>(
        "data/image/earthmap.jpg"
    );
    auto image_lambert = std::make_shared<Lambertian>(image_texture);

    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(0, -500, 0), 500),
            image_lambert
        ));

    for(int a = -11; a <= 11; a++) {
        for(int b = -11; b <= 11; b++) {
            vec3 albedo = vec3::random() * vec3::random();
            // vec3 albedo = vec3(1.0f);
            vec3 center(a * random_double() * 2, 1.0, b * random_double() * 2);

            double rnd = random_double();
            std::shared_ptr<Material> mat;
            if(rnd < 0.5f) mat = std::make_shared<Lambertian>(albedo);
            else if(rnd < 0.7f) mat = std::make_shared<Dielectric>(albedo, 1.52f);
            else if(rnd < 0.9f) mat = std::make_shared<Metal>(albedo, 0.03f);
            else mat = std::make_shared<Emitter>(std::make_shared<ConstantTexture>(albedo), 10.0f);
            primitives.emplace_back(
                std::make_shared<ShapePrimitive>(
                    createSphereShape(center, random_double()*0.75f),
                    mat
                ));
        }
    }
    
    auto bunny = createTriangleMesh("data/model/bunny.obj", vec3(0.0, 1.0, 0.0), 40.0, vec3(1, 1, 1), true);
    auto bunny_emit = std::make_shared<Emitter>(std::make_shared<ConstantTexture>(vec3(1.0f, 1.0f, 1.0f)), 10.0f);
    for (auto &triangle : bunny){
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(
                triangle, bunny_emit
            ));
    }
    
    return primitives;
}