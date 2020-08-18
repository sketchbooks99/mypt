#ifndef object_test_h
#define object_test_h

#include "../src/Util.h"
#include "../src/Hittable_list.h"
#include "../src/Sphere.h"
#include "../src/Material.h"
#include "../src/Triangle_mesh.h"

Hittable_list scene() {
    Hittable_list world;

    auto checker = make_shared<Checker_texture>(
        make_shared<Constant_texture>(vec3(0.2, 0.3, 0.1)),
        make_shared<Constant_texture>(vec3(0.9, 0.9, 0.9))
    );

    world.add(make_shared<Sphere>(
        vec3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)
    ));

    auto albedo = vec3(0.2, 0.8, 0.8);
    world.add(make_shared<Triangle_mesh>(
        "../model/bunny.obj", vec3(0.0, 1.0, 0.0), 1.0, vec3(1, -1, 1), 
        make_shared<Lambertian>(make_shared<Constant_texture>(albedo))));
    
    return world;
}

#endif