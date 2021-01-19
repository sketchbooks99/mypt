#include "Scene.h"
#include <fstream>
#include <sstream>

#include "../shape/MovingSphere.h"
#include "../shape/Plane.h"
#include "../shape/Sphere.h"
#include "../shape/Triangle.h"

#include "../material/Lambertian.h"
#include "../material/Metal.h"
#include "../material/Dielectric.h"
#include "../material/NormalMat.h"
#include "../material/Emitter.h"
#include "../material/Isotropic.h"
/// INVERT:
#include "../material/MMAPs.h"
#include "../material/Absorber.h"

#include "../texture/ConstantTexture.h"
#include "../texture/ImageTexture.h"
#include "../texture/CheckerTexture.h"
#include "../texture/NoiseTexture.h"

namespace mypt {

// -----------------------------------------------------------------------------------------
Scene::Scene(const std::string& filename) {    
    std::ifstream ifs(filename, std::ios::in);
    ASSERT(ifs.is_open(), "The scene file '"+filename+"' is not existed\n");

    int image_width = 512, image_height = 512;
    depth = 5;
    samples_per_pixel = 1;
    is_invert = false;
    bool is_comment = false;

    std::string refpath = "result/ref.png";

    while(!ifs.eof()) {
        std::string line;
        // When line has no characters.
        if(!std::getline(ifs, line)) continue;

        // Create string stream
        std::istringstream iss(line);
        std::string header;
        iss >> header;

        if(header == "beginComment") is_comment = true;
        else if(header == "endComment") is_comment = false;

        if(is_comment) continue;

        // `#` is comment
        if(header == "#" || header[0] == '#') continue;

        if(header == "filename")
            iss >> image.first;
        else if(header == "ref") {
            is_invert = true;
            iss >> refpath;
        }
        else if (header == "width")
            iss >> image_width;
        else if (header == "height")
            iss >> image_height;
        else if (header == "inv")
            iss >> absorbed_image.first;
        else if(header == "spp" || header == "samples_per_pixel")
            iss >> samples_per_pixel;
        else if(header == "depth")
            iss >> depth;
        else if(header == "beginCamera")
            createCamera(ifs, double(image_width)/image_height);
        else if(header == "beginPrimitive")
            createPrimitive(ifs);
        else if(header == "beginLight")
            createLight(ifs);
        else if(header == "translate") {
            float x, y, z;
            iss >> x >> y >> z;
            ts.translate(vec3(x, y, z));
        }
        else if(header == "rotate") {
            float angle, x, y, z;
            iss >> angle >> x >> y >> z;
            ts.rotate(degrees_to_radians(angle), vec3(x, y, z));
        }
        else if(header == "rotate_x") {
            float angle;
            iss >> angle;
            ts.rotateX(degrees_to_radians(angle));
        }
        else if(header == "rotate_y") {
            float angle;
            iss >> angle;
            ts.rotateY(degrees_to_radians(angle));
        }
        else if(header == "rotate_z") {
            float angle;
            iss >> angle;
            ts.rotateZ(degrees_to_radians(angle));
        }
    }
    integrator = Integrator();
    // Create out image with same dimensions of refimage.
    if(is_invert) {
        refimage.load(refpath);
        image.second.build(refimage.getWidth(), refimage.getHeight());
    } else {
        image.second.build(image_width, image_height);
    }
}

// -----------------------------------------------------------------------------------------
void Scene::createCamera(std::ifstream& ifs, double aspect) {
    // Default configuration of camera.
    vec3 origin(0, 0, 100);
    vec3 lookat(0, 0, 0);
    vec3 up(0, 1, 0);
    double focus_length = 15.0;
    double aperture = 0.0;
    double vfov = 20.0;

    while(true)
    {
        std::string line;
        if(!std::getline(ifs, line)) continue;

        std::istringstream iss(line);
        std::string header;
        iss >> header;

        if(header == "endCamera") break;
        else if(header == "origin")
            iss >> origin.x >> origin.y >> origin.z;
        else if(header == "lookat")
            iss >> lookat.x >> lookat.y >> lookat.z;
        else if(header == "up")
            iss >> up.x >> up.y >> up.z;
        else if(header == "focus_length")
            iss >> focus_length;
        else if(header == "aperture")
            iss >> aperture;
        else if(header == "vfov")
            iss >> vfov;
    }
    camera = Camera(origin, lookat, up, vfov, aspect, aperture, focus_length, 0.0, 1.0);
}

// -----------------------------------------------------------------------------------------
void Scene::createShapes(std::istringstream& iss, std::vector<std::shared_ptr<Shape>>& shapes) {
    std::string type, header;
    while(!iss.eof()) {
        iss >> type;
        if(type == "plane") {
            vec2 min(-1,-1), max(1,1);
            while(!iss.eof()) {
                iss >> header;
                if(header == "min") 
                    iss >> min[0] >> min[1];
                else if(header == "max")
                    iss >> max[0] >> max[1];
            }
            shapes.emplace_back(createPlaneShape(min, max));
        } 
        else if(type == "sphere") {
            double radius = 1.0;
            while(!iss.eof()) {
                iss >> header;
                if(header == "radius")
                    iss >> radius;
            }
            shapes.emplace_back(createSphereShape(radius));   
        }
        else if(type == "mesh") {
            std::string filename;
            vec3 axis = vec3(1,1,1);
            double size = 50;
            bool isSmooth = false;
            iss >> header;
            while(!iss.eof()) {
                if(header == "filename")
                    iss >> filename;
                else if(header == "axis") 
                    iss >> axis.x >> axis.y >> axis.z;
                else if(header == "size")
                    iss >> size;
                else if(header == "smooth")
                    isSmooth = true;
                iss >> header;
            }
            for(auto &triangle : createTriangleMesh(filename, size, axis, isSmooth)) 
                shapes.emplace_back(triangle);
        }
    }

}

// -----------------------------------------------------------------------------------------
auto Scene::createMaterial(std::istringstream& iss) {
    std::shared_ptr<Material> material;
    std::string type, header;
    while(!iss.eof()) {
        iss >> type;
        if(type == "lambertian" || type == "emitter") {
            float intensity = 1.0f;
            std::shared_ptr<Texture> texture;
            iss >> header;
            while(!iss.eof()) {
                if(header == "color") {
                    vec3 albedo(0.8);
                    iss >> albedo.x >> albedo.y >> albedo.z;
                    texture = std::make_shared<ConstantTexture>(albedo);
                }
                else if(header == "checker") {
                    vec3 color1 = vec3(0.3f), color2 = vec3(1.0f);
                    iss >> header;
                    if(header == "color1") 
                        iss >> color1.x >> color1.y >> color1.z;
                    if(header == "color2") 
                        iss >> color2.x >> color2.y >> color2.z;
                    texture = std::make_shared<CheckerTexture>(color1, color2);
                }
                else if(header == "image") {
                    std::string filename;
                    iss >> filename;
                    texture = std::make_shared<ImageTexture>(filename);
                }
                else if(header == "noise") {
                    double scale = 1.0f;
                    iss >> header;
                    if(header == "scale") iss >> scale;
                    iss >> header;
                    NoiseTexture::Mode noiseType { NoiseTexture::Mode::NOISE };
                    if(header == "turb") noiseType = NoiseTexture::Mode::TURB;
                    texture = std::make_shared<NoiseTexture>(scale, noiseType);
                }
                else if(header == "intensity")
                    iss >> intensity;
                iss >> header;
            }
            if(type == "lambertian") material = std::make_shared<Lambertian>(texture);
            else                     material = std::make_shared<Emitter>(texture, intensity);
        }
        else if(type == "metal" || type == "mmaps") {
            vec3 color(1.0);
            double fuzz = 0.0;
            while(!iss.eof()) {
                iss >> header;
                if(header == "color")
                    iss >> color.x >> color.y >> color.z;
                else if(header == "fuzz")
                    iss >> fuzz;
            }
            material = std::make_shared<MMAPs>(color, fuzz);
        }
        else if(type == "dielectric") {
            vec3 color(1.0);
            float ior = 1.52f;
            bool is_normal = false;
            while(!iss.eof()) {
                iss >> header;
                if(header == "color")
                    iss >> color.x >> color.y >> color.z;
                else if(header == "ior")
                    iss >> ior;
                else if(header == "normal")
                    is_normal = true;
            }
            material = std::make_shared<Dielectric>(color, ior, is_normal);
        }
        else if(type == "normal") {
            bool is_emit = false;
            while(!iss.eof()) {
                iss >> header;
                if(header == "emit") is_emit = true;
            }
            material = std::make_shared<NormalMat>(is_emit);
        }
        /// INVERT:
        else if(type == "absorber") {
            int w = 512, h = 512;
            while(!iss.eof()) {
                iss >> header;
                if(header == "width") iss >> w;
                else if(header == "height") iss >> h;
            }
            absorbed_image.second = std::make_shared<Image<RGBA>>(w, h);
            material = std::make_shared<Absorber<RGBA>>(absorbed_image.second);
        }
    }
    return material;
}

// -----------------------------------------------------------------------------------------
void Scene::createPrimitive(std::ifstream& ifs) {
    std::vector<std::shared_ptr<Shape>> shapes;
    std::shared_ptr<Material> material;

    // Push back transform to independently apply transformation to primitives.
    ts.pushMatrix();

    while(true) {
        std::string line;
        if(!std::getline(ifs, line)) continue;

        std::istringstream iss(line);
        std::string header;
        iss >> header;

        if(header == "endPrimitive") break;

        // Shape ------------------------------------
        else if(header == "shape") this->createShapes(iss, shapes);
        // Material ---------------------------------
        else if(header == "material") material = this->createMaterial(iss);
        // Transformation ---------------------------
        else if(header == "translate") {
            float x, y, z;
            iss >> x >> y >> z;
            ts.translate(vec3(x, y, z));
        }
        else if(header == "rotate") {
            float angle, x, y, z;
            iss >> angle >> x >> y >> z;
            ts.rotate(degrees_to_radians(angle), vec3(x, y, z));
        }
        else if(header == "rotate_x") {
            float angle;
            iss >> angle;
            ts.rotateX(degrees_to_radians(angle));
        }
        else if(header == "rotate_y") {
            float angle;
            iss >> angle;
            ts.rotateY(degrees_to_radians(angle));
        }
        else if(header == "rotate_z") {
            float angle;
            iss >> angle;
            ts.rotateZ(degrees_to_radians(angle));
        }
    }

    ASSERT(!shapes.empty(), "Shape object is required to primitive\n");
    if(!material) material = std::make_shared<Lambertian>(vec3(0.8f));

    for(auto &shape : shapes) {
        this->primitives.emplace_back(std::make_shared<ShapePrimitive>(
            shape, material, std::make_shared<Transform>(ts.getCurrentTransform())));
    }

    ts.popMatrix();
}

// -----------------------------------------------------------------------------------------
void Scene::createLight(std::ifstream& ifs) {
    std::vector<std::shared_ptr<Shape>> shapes;
    std::shared_ptr<Material> emitter;
    float intensity = 1.0f;
    std::shared_ptr<Texture> texture;

    ts.pushMatrix();
    while(true) {
        std::string line;
        if(!std::getline(ifs, line)) continue;

        std::istringstream iss(line);
        std::string header;
        iss >> header;

        if(header == "endLight") break;

        // Shape -----------------------------------
        else if(header == "shape") {
            this->createShapes(iss, shapes);
        }
        // Texture ----------------------------------
        else if(header == "color") {
            vec3 albedo;
            iss >> albedo.x >> albedo.y >> albedo.z;
            texture = std::make_shared<ConstantTexture>(albedo);
        }
        else if(header == "checker") {
            vec3 color1 = vec3(0.3f), color2 = vec3(1.0f);
            iss >> header;
            if(header == "color1") 
                iss >> color1.x >> color1.y >> color1.z;
            if(header == "color2") 
                iss >> color2.x >> color2.y >> color2.z;
            texture = std::make_shared<CheckerTexture>(color1, color2);
        }
        else if(header == "image") {
            std::string filename;
            iss >> filename;
            texture = std::make_shared<ImageTexture>(filename);
        }
        else if(header == "noise") {
            double scale = 1.0f;
            iss >> header;
            if(header == "scale") iss >> scale;
            iss >> header;
            NoiseTexture::Mode noiseType { NoiseTexture::Mode::NOISE };
            if(header == "turb") noiseType = NoiseTexture::Mode::TURB;
            texture = std::make_shared<NoiseTexture>(scale, noiseType);
        }
        else if(header == "intensity")
            iss >> intensity;
        // Transformation ---------------------------
        else if(header == "translate") {
            float x, y, z;
            iss >> x >> y >> z;
            ts.translate(vec3(x, y, z));
        }
        else if(header == "rotate") {
            float angle, x, y, z;
            iss >> angle >> x >> y >> z;
            ts.rotate(degrees_to_radians(angle), vec3(x, y, z));
        }
        else if(header == "rotate_x") {
            float angle;
            iss >> angle;
            ts.rotateX(degrees_to_radians(angle));
        }
        else if(header == "rotate_y") {
            float angle;
            iss >> angle;
            ts.rotateY(degrees_to_radians(angle));
        }
        else if(header == "rotate_z") {
            float angle;
            iss >> angle;
            ts.rotateZ(degrees_to_radians(angle));
        }
    }

    ASSERT(!shapes.empty(), "Shape object is required to primitive\n");
    if(!texture) texture = std::make_shared<ConstantTexture>(vec3(1.0f));
    emitter = std::make_shared<Emitter>(texture, intensity);

    for(auto &shape : shapes) {
        this->lights.emplace_back(std::make_shared<ShapePrimitive>(
            shape, emitter, std::make_shared<Transform>(ts.getCurrentTransform())));
        this->primitives.emplace_back(std::make_shared<ShapePrimitive>(
            shape, emitter, std::make_shared<Transform>(ts.getCurrentTransform())));
    }

    ts.popMatrix();
}

// -----------------------------------------------------------------------------------------
void Scene::streamProgress(int currentLine, int maxLine, double elapsedTime, int progressLen) {    
    // Display progress bar
    std::cerr << "\rRendering: [";
    int progress = static_cast<int>(((float)(currentLine+1) / maxLine) * progressLen);
    for(int i=0; i<progress; i++) 
        std::cerr << "+";
    for(int i=0; i<progressLen-progress; i++)
        std::cerr << " ";
    std::cerr << "]";

    std::cerr << " [" << std::fixed << std::setprecision(2) << elapsedTime << "s]";

    // Display percentage of process
    float percent = (float)(currentLine+1) / maxLine;
    std::cerr << " (" << std::fixed << std::setprecision(2) << (float)(percent * 100.0f) << "%, ";
    std::cerr << "" << currentLine + 1 << " / " << maxLine << ")" << std::flush;
}

// -----------------------------------------------------------------------------------------
void Scene::render() {

    std::cout << "primitives: " << this->primitives.size() << std::endl;
    std::cout << "lights: " << this->lights.size() << std::endl;

    BVH bvh(this->primitives, 0, this->primitives.size(), 1, BVH::SplitMethod::MIDDLE);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);

    int progress_len = 20;

    auto width = image.second.getWidth();
    auto height = image.second.getHeight();

    #ifdef _OPENMP
    int n_threads = omp_get_max_threads();
    #endif

    // ASSERT(refimage.getWidth() == width && refimage.getHeight() == height, "The reference image and rendering image should have same dimensions!");

    // declare reduction for vec3
    for(int y=0; y<height; y++) {
        clock_gettime(CLOCK_REALTIME, &end_time);
        double sec = end_time.tv_sec - start_time.tv_sec;
        double nsec = (double)(end_time.tv_nsec - start_time.tv_nsec) / 1000000000;
        double elapsed_time = sec + nsec;
        this->streamProgress(y, height, elapsed_time, progress_len);

        #ifdef _OPENMP
        #pragma omp parallel for num_threads(n_threads)
        #endif
        for(int x=0; x<width; x++) {
            vec3 color(0,0,0);
            RGBA pixel_color;
            if(is_invert) {
                pixel_color = refimage.get(x, y);
                // Skip tracing scene when pixel_color had no colors or was completely black.
                if(vec3(pixel_color.x, pixel_color.y, pixel_color.z).length() == 0) continue;
            }
                
            for(int s=0; s<samples_per_pixel; s++) {
                auto u = (x + random_double()) / width;
                auto v = (y + random_double()) / height;

                Ray r = camera.get_ray(u, v);
                r.set_color(pixel_color);
                color += integrator.trace(r, bvh, lights, background, depth);
            }
            RGBA rgb_color = RGBA(vec2color(color, 1.0 / samples_per_pixel), 255);
            image.second.set(x, height-(y+1), rgb_color);
        }
    }

    std::string file_format = split(image.first, '.').back();
    image.second.write(image.first, file_format);
    
    if(is_invert) {
        std::cout << "\nWrite absorbed result" << std::endl;
        absorbed_image.second->write(absorbed_image.first, split(absorbed_image.first, '.').back());
    }
    std::cerr << "\nDone\n";
}

}