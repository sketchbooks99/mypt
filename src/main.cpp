//
//  main.cpp
//  RayTracing
//
//  Created by 木内舜司 on 2020/04/11.
//  Copyright © 2020 木内舜司. All rights reserved.
//

#include "Util.h"

#include "Hittable_list.h"
#include "Sphere.h"
#include "Moving_Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "../scene/object_test.h"

#include <iostream>

Hittable_list random_scene() {
    Hittable_list world;

    // ground Sphere 
    auto checker = make_shared<Checker_texture>(
        make_shared<Constant_texture>(vec3(0.2, 0.3, 0.1)),
        make_shared<Constant_texture>(vec3(0.9, 0.9, 0.9))
    );
    world.add(make_shared<Sphere>(
        vec3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));
    
    for(int a = -5; a < 5; a++) {
        for(int b = -5; b < 5; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            if((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if(choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    world.add(make_shared<Moving_sphere>(
                        center, center + vec3(0, random_double(0, 0.5), 0), 0.0, 1.0, 0.2,
                        make_shared<Lambertian>(make_shared<Constant_texture>(albedo))));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    world.add(
                        make_shared<Sphere>(center, 0.2, make_shared<Metal>(albedo, fuzz)));
                } else {
                    // glass
                    world.add(make_shared<Sphere>(center, 0.2, make_shared<Dielectric>(1.5)));
                }
            }
        }
    }

    world.add(make_shared<Sphere>(vec3(0, 1, 0), 1.0, make_shared<Dielectric>(1.5)));

    world.add(make_shared<Sphere>(vec3(-4, 1, 0), 1.0, make_shared<Lambertian>(make_shared<Constant_texture>(vec3(0.4, 0.2, 0.1)))));

    world.add(make_shared<Sphere>(vec3(4, 1, 0), 1.0, make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    return world;
}

Hittable_list two_perlin_Spheres() {
    Hittable_list objects;

    auto pertext = make_shared<Noise_texture>(4);
    objects.add(make_shared<Sphere>(vec3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    objects.add(make_shared<Sphere>(vec3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    return objects;
}

vec3 ray_color(const Ray& r, const Hittable& world, int depth) {
    Hit_record rec;
    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if(depth <= 0) 
        return vec3(0, 0, 0);

    if(world.hit(r, 0, infinity, rec)) {
        Ray scattered;
        vec3 attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return vec3(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(int argc, const char * argv[]) {
    const int image_width = 500;
    const int image_height = 250;
    const int samples_per_pixel = 1;
    const int max_depth = 50;
    const auto aspect_ratio = double(image_width) / image_height;
    
    std::cout << "P3\n" << image_width << '_' << image_height << "\n255\n";

    auto world = scene();

    vec3 lookfrom(13,2,3);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    for(int j = image_height-1; j >= 0; j--) {
        // if(j % 20 == 0) std::cerr << "Scanlines remaining: " << j << std::endl;
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < image_width; i++) {
            vec3 color(0, 0, 0);
            for(int s = 0; s < samples_per_pixel; s++) {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                Ray r = cam.get_ray(u, v);
                color += ray_color(r, world, max_depth);
            }
            color.write_color(std::cout, samples_per_pixel);
        }
    }
    std::cerr << "\nDone\n";
}
