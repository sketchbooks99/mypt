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
    int depth = 5;
    while(!ifs.eof()) {
        std::string line;
        // When line has no characters.
        if(!std::getline(ifs, line)) continue;

        // Create string stream
        std::istringstream iss(line);
        std::string header;
        iss >> header;
        if(header == "filename")
            iss >> image_name;
        else if(header == "width")
            iss >> image_width;
        else if(header == "height")
            iss >> image_height;
        else if(header == "spp" || header == "samples_per_pixel")
            iss >> samples_per_pixel;
        else if(header == "depth")
            iss >> depth;
        else if(header == "background") 
            iss >> background.x >> background.y >> background.z;
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
    image.build(image_width, image_height);
}

void Scene::createCamera(std::ifstream& ifs, double aspect) {
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
void Scene::createPrimitive(std::ifstream& ifs) {
    std::vector<std::shared_ptr<Shape>> shapes;
    std::shared_ptr<Material> mat;
    ts.pushMatrix();
    while(true) {
        std::string line;
        if(!std::getline(ifs, line)) continue;

        std::istringstream iss(line);
        std::string header;
        iss >> header;

        if(header == "endPrimitive") break;

        // Shape ------------------------------------
        else if(header == "shape") {
            std::string type;
            iss >> type;
            if(type == "plane") {
                vec2 min, max;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "min") 
                        iss >> min[0] >> min[1];
                    else if(header == "max")
                        iss >> max[0] >> max[1];
                }
                shapes.emplace_back(createPlaneShape(min, max));
            } else if(type == "sphere") {
                double radius;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "radius")
                        iss >> radius;
                }
                shapes.emplace_back(createSphereShape(radius));   
            } else if(type == "mesh") {
                std::string filename;
                vec3 axis = vec3(1,1,1);
                double size = 50;
                bool isSmooth = false;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "filename")
                        iss >> filename;
                    else if(header == "axis") 
                        iss >> axis.x >> axis.y >> axis.z;
                    else if(header == "size")
                        iss >> size;
                    else if(header == "smooth")
                        isSmooth = true;
                }
                for(auto &triangle : createTriangleMesh(filename, size, axis, isSmooth)) 
                    shapes.emplace_back(triangle);
            }
        }
        // Material ---------------------------------
        if(header == "material") {
            std::string type;
            iss >> type;
            if(type == "lambertian" || type == "emitter") {
                float intensity = 1.0f;
                std::shared_ptr<Texture> texture;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "color") {
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
                        NoiseTexture::Mode noiseType;
                        if(header == "noise")     noiseType = NoiseTexture::Mode::NOISE;
                        else if(header == "turb") noiseType = NoiseTexture::Mode::TURB;
                        texture = std::make_shared<NoiseTexture>(scale, noiseType);
                    }
                    else if(header == "intensity")
                        iss >> intensity;
                }
                if(type == "lambertian") mat = std::make_shared<Lambertian>(texture);
                else                     mat = std::make_shared<Emitter>(texture, intensity);
            }
            else if(type == "metal") {
                vec3 color(0.9, 0.7, 0.3);
                double fuzz = 0.01;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "color")
                        iss >> color.x >> color.y >> color.z;
                    else if(header == "fuzz")
                        iss >> fuzz;
                }
                mat = std::make_shared<Metal>(color, fuzz);
            }
            else if(type == "dielectric") {
                vec3 color(0.9, 0.7, 0.3);
                double ior = 1.52;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "color")
                        iss >> color.x >> color.y >> color.z;
                    else if(header == "ior")
                        iss >> ior;
                }
                mat = std::make_shared<Dielectric>(color, ior);
            }
            else if(type == "normal") {
                mat = std::make_shared<NormalMat>();
            }
        }
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
    ts.popMatrix();

    ASSERT(!shapes.empty(), "Shape object is required to primitive\n");
    if(!mat) mat = std::make_shared<Lambertian>(vec3(0.8f));

    for(auto &shape : shapes) {
        this->primitives.emplace_back(shape, mat, std::make_shared<Transform>(ts.getCurrentTransform()));
    }
}

// -----------------------------------------------------------------------------------------
void Scene::createLight(std::ifstream& ifs) {
    std::vector<std::shared_ptr<Shape>> shapes;
    std::shared_ptr<Emitter> emitter;
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
            std::string type;
            iss >> type;
            if(type == "plane") {
                vec2 min, max;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "min") 
                        iss >> min[0] >> min[1];
                    else if(header == "max")
                        iss >> max[0] >> max[1];
                }
                shapes.emplace_back(createPlaneShape(min, max));
            } else if(type == "sphere") {
                double radius;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "radius")
                        iss >> radius;
                }
                shapes.emplace_back(createSphereShape(radius));   
            } else if(type == "mesh") {
                std::string filename;
                vec3 axis = vec3(1,1,1);
                double size = 50;
                bool isSmooth = false;
                while(!iss.eof()) {
                    iss >> header;
                    if(header == "filename")
                        iss >> filename;
                    else if(header == "axis") 
                        iss >> axis.x >> axis.y >> axis.z;
                    else if(header == "size")
                        iss >> size;
                    else if(header == "smooth")
                        isSmooth = true;
                }
                for(auto &triangle : createTriangleMesh(filename, size, axis, isSmooth)) 
                    shapes.emplace_back(triangle);
            }
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
            NoiseTexture::Mode noiseType;
            if(header == "noise")     noiseType = NoiseTexture::Mode::NOISE;
            else if(header == "turb") noiseType = NoiseTexture::Mode::TURB;
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
    ts.popMatrix();

    ASSERT(!shapes.empty(), "Shape object is required to primitive\n");
    if(!texture) texture = std::make_shared<ConstantTexture>(vec3(1.0f));
    emitter = std::make_shared<Emitter>(texture, intensity);

    for(auto &shape : shapes) {
        this->primitives.emplace_back(shape, emitter, std::make_shared<Transform>(ts.getCurrentTransform()));
    }
}

void Scene::streamProgress(int currentLine, int maxLine, double elapsedTime, int progressLen) {    
    // Display progress bar
    std::cerr << "\rRendering: [";
    int progress = static_cast<int>(((float)(currentLine+1) / maxLine) * progressLen);
    for(int i=0; i<progress; i++) 
        std::cerr << "+";
    for(int i=0; i<progressLen-progress; i++)
        std::cerr << " ";
    std::cerr << "]";

    std::cerr << " [" << std::fixed << std::setprecision(2) << elapsedTime / CLOCKS_PER_SEC << "s]";

    // Display percentage of process
    float percent = (float)(currentLine+1) / maxLine;
    std::cerr << " (" << std::fixed << std::setprecision(2) << (float)(percent * 100.0f) << "%, ";
    std::cerr << "" << currentLine + 1 << " / " << maxLine << ")" <<std::flush;
}

// -----------------------------------------------------------------------------------------
void Scene::render() {
    BVH bvh(primitives, 0, primitives.size(), 1, BVH::SplitMethod::SAH);

    int progress_len = 20;
    clock_t start_time = clock();

    auto width = image.getWidth();
    auto height = image.getHeight();

    for(int y=0; y<height; y++) {
        double elapsed_time = static_cast<double>(clock() - start_time);
        this->streamProgress(y, height, elapsed_time, progress_len);

        for(int x=0; x<width; x++) {
            vec3 color(0, 0, 0);
            for(int s=0; s<samples_per_pixel; s++) {
                auto u = (x + random_double()) / width;
                auto v = (y + random_double()) / height;

                Ray r = camera.get_ray(u, v);
                color += integrator.trace(r, bvh, lights.back(), background, depth);
            }
        }
        auto scale = 1.0 / samples_per_pixel;
        auto r = sqrt(scale * color.x);
        auto g = sqrt(scale * color.y);
        auto b = sqrt(scale * color.z);
        RGBA rgb_color(static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999)),
                        static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999)),
                        static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999)),
                        255);
        image.set(x, image_height-(y+1), rgb_color);
    }

    image.write(image_name, "PNG");
    std::cerr << "\nDone\n";
}

}