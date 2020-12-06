#pragma once

#include "../src/core/PBRenderer.h"

std::vector<std::shared_ptr<Primitive>> scene() {
    std::vector<std::shared_ptr<Primitive>> primitives;
    TransformSystem ts;
    
    auto noise_texture = std::make_shared<NoiseTexture>(
        1.0f, NoiseTexture::Mode::TURB);
    auto ground_lambert = std::make_shared<Lambertian>(noise_texture);

    // ground
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createSphereShape(vec3(0, -1000, 0), 1000),
            ground_lambert,
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));

    float sphere_field = 50.0f;
    const int num_sphere = 300;
    for(int i=0; i<num_sphere; i++) {
        auto x = (random_double() * 2.0f - 1.0f) * sphere_field;
        auto y = random_double() * 5.0f + 2.5f;
        auto z = (random_double() * 2.0f - 1.0f) * sphere_field;
        auto albedo = vec3::random() * vec3::random();
        
        double rnd = random_double();
        std::shared_ptr<Material> mat_ptr;
        if(rnd < 0.5f) mat_ptr = std::make_shared<Lambertian>(albedo);
        else if(rnd < 0.7f) mat_ptr = std::make_shared<Dielectric>(albedo, 1.52);
        else if(rnd < 0.9f) mat_ptr = std::make_shared<Metal>(albedo, 0.0f);
        else mat_ptr = std::make_shared<Emitter>(albedo, 10.0f);

        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(
                createSphereShape(vec3(x,y,z), random_double()*2+1.0f),
                mat_ptr,
                std::make_shared<Transform>(ts.getCurrentTransform())
            ));
    }
    
    // emissive texture
    auto white_texture = std::make_shared<ConstantTexture>(vec3(1.0f));
    auto emissive = std::make_shared<Emitter>(white_texture, 5.0f);
    primitives.emplace_back(
        std::make_shared<ShapePrimitive>(
            createPlaneShape(vec2(-5, -5), vec2(5, 5), 15.0f,
                Plane::PlaneAxis::XZ),
            emissive,
            std::make_shared<Transform>(ts.getCurrentTransform())
        ));
    
    // bunny 1

    auto albedo = vec3(0.8, 0.05, 0.05);
    std::shared_ptr<Material> bunny_lambert = std::make_shared<Lambertian>(albedo);
    auto bunny = createTriangleMesh("data/model/bunny.obj", vec3(15,5,0), 50.0f, vec3(1,1,1), true);
    auto bunny_transform = std::make_shared<Transform>(ts.getCurrentTransform());

    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(triangle, bunny_lambert, bunny_transform));
    }
    
    // bunny 2

    albedo = vec3(0.80, 0.80, 0.05);
    bunny_lambert = std::make_shared<Metal>(albedo, 0.0f);
    bunny = createTriangleMesh("data/model/bunny.obj", vec3(5,5,0), 50.0f, vec3(1,1,1), true);
    bunny_transform = std::make_shared<Transform>(ts.getCurrentTransform());

    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(triangle, bunny_lambert, bunny_transform));
    }

    // bunny 3

    albedo = vec3(0.05, 0.05, 0.80);
    bunny_lambert = std::make_shared<Dielectric>(albedo, 1.52f);
    bunny = createTriangleMesh("data/model/bunny.obj", vec3(-5,5,0), 50.0f, vec3(1,1,1), true);
    bunny_transform = std::make_shared<Transform>(ts.getCurrentTransform());

    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(triangle, bunny_lambert, bunny_transform));
    }


    // bunny 4


    albedo = vec3(1.0f);
    bunny_lambert = std::make_shared<Lambertian>(albedo);
    bunny = createTriangleMesh("data/model/bunny.obj", vec3(-15,5,0), 50.0f, vec3(1,1,1), true);
    bunny_transform = std::make_shared<Transform>(ts.getCurrentTransform());

    for(auto &triangle : bunny) {
        primitives.emplace_back(
            std::make_shared<ShapePrimitive>(triangle, bunny_lambert, bunny_transform));
    }


    return primitives;
}