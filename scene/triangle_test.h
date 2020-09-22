#ifndef triangle_test_h
#define triangle_test_h

#include "../src/core/PBRenderer.h"

Hittable_list scene() {
    Hittable_list world;
    
    auto checker = make_shared<Checker_texture>(
        make_shared<Constant_texture>(vec3(0.2, 0.3, 0.1)),
        make_shared<Constant_texture>(vec3(0.9, 0.9, 0.9))
    );

    world.add(make_shared<Sphere>(
        vec3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)
    ));

    int num_Triangle = 100;
    for (int i = -num_Triangle/2; i < num_Triangle/2; i++) {
        float space_scale = 2.0;
        vec3 center(random_double(-1,1) * space_scale, 0.2, random_double(-1,1) * space_scale);
        auto scale = (random_double() - 0.5) * 5.0;

        vec3 v[3]; // Triangle vertices
        for(int j=0; j<3; j++) {
            auto offset = vec3::random(-1,1) * vec3::random(-1,1);
            v[j] = center + offset;
        }

        auto choose_mat = random_double();
        if(choose_mat < 0.8) {
            // diffuse
            auto albedo = vec3::random() * vec3::random();
            world.add(make_shared<Triangle>(v[0], v[1], v[2], make_shared<Lambertian>(make_shared<Constant_texture>(albedo))));
        } else if(choose_mat < 0.95) {
            // glass
            auto albedo = vec3::random(.5, 1);
            auto fuzz = random_double(0, .5);
            world.add(
                make_shared<Triangle>(v[0], v[1], v[2], make_shared<Metal>(albedo, fuzz))
            );
        } else {
            // glass
            world.add(make_shared<Triangle>(v[0], v[1], v[2], make_shared<Dielectric>(1.5)));
        }
    }

    return world;
}

#endif