#include "core/PBRenderer.h"
#include "../scene/planeandbunny.h"

vec3 ray_color(const Ray& r, const BVH* bvh, const vec3& background, int depth) {
    HitRecord rec;
    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if(depth <= 0)
        return vec3(0, 0, 0);

    if(!bvh->intersect(r, 0, infinity, rec))
        return background;

    Ray scattered;
    vec3 attenuation;
    vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if(!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;
    return emitted + attenuation * ray_color(scattered, bvh, background, depth-1);
}

int main(int argc, const char * argv[]) {
    // Change seed of randaom value
    srand((unsigned)time(NULL));

    std::string outname = "result/image.png";

    int image_width = 1024;
    int image_height = 768;
    int samples_per_pixel = 1024;
    int max_depth = 5;
    auto aspect_ratio = double(image_width) / image_height;

    vec3 lookfrom(-20, 20, 50);
    vec3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 15.0;
    auto aperture = 0.0;
    // vec3 background(0.7, 0.9, 0.9);
    vec3 background(1.0f);

    // Parsing scene configuration
    std::string filename = argv[1];
    if(filename != "") {
        std::ifstream ifs(filename, std::ios::in);
        ASSERT(ifs.is_open(), "The scene file '"+filename+"' is not existed\n");
        while (!ifs.eof()) {
            std::string line;
            // When line has no characters.
            if(!std::getline(ifs, line)) break;
            
            // Create string stream
            std::istringstream iss(line);
            std::string header;
            iss >> header;
            
            if(header == "filename") 
                iss >> outname;
            else if(header == "width")
                iss >> image_width;
            else if(header == "height")
                iss >> image_height;
            else if(header == "spp" || header == "samples_per_pixels")
                iss >> samples_per_pixel;
            else if(header == "depth")
                iss >> max_depth;
            else if(header == "origin") {
                float x, y, z;
                iss >> x >> y >> z;
                lookfrom = vec3(x, y, z);
            }
            else if(header == "lookat") {
                float x, y, z;
                iss >> x >> y >> z;
                lookat = vec3(x, y, z);
            }
            else if(header == "up") {
                float x, y, z;
                iss >> x >> y >> z;
                vup = vec3(x, y, z);
            }
            else if(header == "focus_length" || header == "focus")
                iss >> dist_to_focus;
            else if(header == "aperture")
                iss >> aperture;
        }
    }

    // Verify config is successfully loaded
    std::cout << "filename: " << outname << std::endl;
    std::cout << "width: " << image_width << ", height: " << image_height << std::endl; 
    std::cout << "spp: " << samples_per_pixel << ", depth: " << max_depth << std::endl; 
    std::cout << "origin: " << lookfrom << ", lookat: " << lookat << ", up: " << vup << std::endl;
    std::cout << "focus_length: " << dist_to_focus << ", aperture: " << aperture << std::endl;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto primitives = scene();

    auto bvh = new BVH(primitives, 0, primitives.size()-1, 1, BVH::SplitMethod::SAH);

    Image<RGBA> result(image_width, image_height);
    int progress = -1, len_progress = 40;

    // Unable to display dicimal with index expression
    std::cout.unsetf(std::ios::scientific);

    clock_t start_time = clock();

    // Render the image
    for(int y = 0; y < image_height; y++) {

        // calculate ratio of progress bar
        if(progress != static_cast<int>(((float)(y+1) / image_height) * len_progress))
        {
            progress = static_cast<int>(((float)(y+1) / image_height) * len_progress);
        }
        
        // Display progress bar
        std::cerr << "\rRendering: [";
        for(int i=0; i<len_progress; i++) {
            std::string progress_char = i < progress ? "+" : " ";
            std::cerr << progress_char;
        }
        std::cerr << "]";
        double time = static_cast<double>(clock() - start_time);
        std::cerr << " [" << std::fixed << std::setprecision(2) << time / CLOCKS_PER_SEC << "s]";

        // Display percentage of process
        float percent = (float)(y+1) / image_height;
        std::cerr << " (" << std::fixed << std::setprecision(2) << (float)(percent * 100.0f) << "%, ";
        std::cerr << "" << y + 1 << " / " << image_height << ")" <<std::flush;

        for(int x = 0; x < image_width; x++) {
            vec3 color(0, 0, 0);
            
            for(int s = 0; s < samples_per_pixel; s++) {
                auto u = (x + random_double()) / image_width;
                auto v = (y + random_double()) / image_height;
                Ray r = cam.get_ray(u, v);
                color += ray_color(r, bvh, background, max_depth);
            }
            auto scale = 1.0 / samples_per_pixel;
            auto r = sqrt(scale * color.x);
            auto g = sqrt(scale * color.y);
            auto b = sqrt(scale * color.z);
            RGBA rgb_color(static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999)),
                           static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999)),
                           static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999)),
                           255);
            result.set(x, image_height-(y+1), rgb_color);
        }
    }

    result.write(outname, "PNG");
    std::cerr << "\nDone\n";
    return 0;
}
