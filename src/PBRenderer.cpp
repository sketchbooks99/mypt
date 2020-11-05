//
//  main.cpp
//  RayTracing
//
//  Created by 木内舜司 on 2020/04/11.
//  Copyright © 2020 木内舜司. All rights reserved.
//

#include "core/PBRenderer.h"
#include "../scene/object_test.h"

#include <iostream>

vec3 ray_color(const Ray& r, const BVH* bvh, int depth) {
    HitRecord rec;
    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if(depth <= 0) 
        return vec3(0, 0, 0);

    if(bvh->intersect(r, 0, infinity, rec)) {
        Ray scattered;
        vec3 attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, bvh, depth-1);
        return vec3(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(int argc, const char * argv[]) {
    const int image_width = 500;
    const int image_height = 250;
    const int samples_per_pixel = 50;
    const int max_depth = 5;
    const auto aspect_ratio = double(image_width) / image_height;
    
    std::cout << "P3\n" << image_width << '_' << image_height << "\n255\n";

    auto primitives = scene();

    auto bvh = new BVH(primitives, 0, primitives.size() - 1);
    // bvh->outBVH();
    
    vec3 lookfrom(20, 2, 5);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 15.0;
    auto aperture = 0.0;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    const std::string filename = "hoge.png";
    Image<RGB> result(image_width, image_height);

    for(int y = image_height - 1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for(int x = 0; x < image_width; x++) {
            vec3 color(0, 0, 0);
            for(int s = 0; s < samples_per_pixel; s++) {
                auto u = (x + random_double()) / image_width;
                auto v = (y + random_double()) / image_height;
                Ray r = cam.get_ray(u, v);
                color += ray_color(r, bvh, max_depth);
            }
            color /= samples_per_pixel;
            RGB rgb_color(static_cast<unsigned char>(color.x * 255),
                          static_cast<unsigned char>(color.y * 255),
                          static_cast<unsigned char>(color.z * 255));
            result.set(x, y, rgb_color);
        }
    }
    result.write(filename, "PNG");
    std::cerr << "\nDone\n";
    return 0;
}
