#ifndef triangle_test_h
#define triangle_test_h

#include "../src/rtweekend.h"
#include "../src/hittable_list.h"
#include "../src/triangle.h"
#include "../src/sphere.h"
#include "../src/material.h"

hittable_list scene() {
    hittable_list world;
    
    auto checker = make_shared<checker_texture>(
        make_shared<constant_texture>(vec3(0.2, 0.3, 0.1)),
        make_shared<constant_texture>(vec3(0.9, 0.9, 0.9))
    );

    world.add(make_shared<sphere>(
        vec3(0, -1000, 0), 1000, make_shared<lambertian>(checker)
    ));

    // int num_triangle = 10;
    // for (int i = 0; i < num_triangle; i++) {
    //     auto albedo = vec3::random() * vec3::random();
    //     vec3 center(i + 10 * random_double(), 0.2, i + 10 * random_double());
    //     auto scale = (random_double() - 0.5) * 1.0;
    //     world.add(make_shared<triangle>(
    //         center + scale * random_double(), center + random_double(), center + random_double(),
    //         make_shared<lambertian>(make_shared<constant_texture>(albedo))
    //     ));
    // }

    // auto albedo = vec3::random() * vec3::random();
    vec3 albedo = vec3(1.0, 0.0, 0.0);
    vec3 center = vec3(0.0, 0.2, 0.0);
    auto scale = 3.0;
    vec3 v0 = center + vec3(-1.0, 0.0, 1.0);
    vec3 v1 = center + vec3(1.0, 0.0, 0.0);
    vec3 v2 = center + vec3(0.0, 10.0, 1.0);
    world.add(make_shared<triangle>(
        v0, v1, v2, make_shared<lambertian>(make_shared<constant_texture>(albedo))
    ));

    return world;
}

#endif