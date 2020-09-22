#ifndef object_test_h
#define object_test_h

#include "../src/core/PBRenderer.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;

    auto checker = std::make_shared<CheckerTexture>(
        std::make_shared<ConstantTexture>(vec3(0.2, 0.3, 0.1)),
        std::make_shared<ConstantTexture>(vec3(0.9, 0.9, 0.9))
    );
    auto checker_lambert = std::make_shared<Lambertian>(checker);

    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(0, -1000, 0), 1000),
            checker_lambert
        ));

    auto albedo = vec3(0.2, 0.8, 0.8);
    auto dielectric = std::make_shared<Dielectric>(1.52);

    for(int a = -11; a <= 11; a++) {
        for(int b = -11; b <= 11; b++) {
            vec3 albedo = vec3::random() * vec3::random();
            vec3 center(a * random_double() * 2, 0.5, b * random_double() * 2);
            primitives.emplace_back(
                std::make_shared<ShapePrimitive>(
                    createSphereShape(center, random_double() * 0.5),
                    std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(albedo))
                ));
        }
    }
    
    auto bunny = createTriangleMesh("../model/bunny.obj", vec3(0.0, 1.0, 0.0), 4.0, vec3(1, -1, 1));
    for (auto &triangle : bunny){
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(
                triangle, dielectric
            ));
    }
    
    return primitives;
}

#endif