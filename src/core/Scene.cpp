#include "Scene.h"

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
    depth = 5;
    samples_per_pixel = 1;
    bool is_comment = false;

    while(!ifs.eof()) {
        std::string line;
        // When line has no characters.
        if(!std::getline(ifs, line)) continue;

        // Create string stream
        std::istringstream iss(line);
        std::string header;
        iss >> header;

        // begin/endComment must be placed at out of primitive description
        if(header == "beginComment") is_comment = true;
        else if(header == "endComment") is_comment = false;

        // Skip parsing comment
        if(header == "#" || header[0] == '#' || is_comment == true) continue;

        if(header == "filename")
            iss >> image.first;
        else if (header == "width")
            iss >> image_width;
        else if (header == "height")
            iss >> image_height;
        else if(header == "spp" || header == "samples_per_pixel")
            iss >> samples_per_pixel;
        else if(header == "depth")
            iss >> depth;
        else if(header == "beginCamera")
            createCamera(ifs, Float(image_width)/image_height);
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
        else if(header == "scale") {
            std::vector<float> scale;
            while(true) {
                float s;
                iss >> s;
                if(iss.eof()) break;

                scale.push_back(s);
            }

            if(scale.size() == 1) ts.scale(scale[0]);
            else if(scale.size() == 3) ts.scale(vec3(scale[0], scale[1], scale[2]));
            else THROW("Input value for scale was incorrect!\n");
        }
    }
    integrator = Integrator();
    image.second.allocate(image_width, image_height);
}

// -----------------------------------------------------------------------------------------
void Scene::createCamera(std::ifstream& ifs, Float aspect) {
    // Default configuration of camera.
    vec3 origin(0, 0, 100);
    vec3 lookat(0, 0, 0);
    vec3 up(0, 1, 0);
    Float focus_length = 15.0;
    Float aperture = 0.0;
    Float vfov = 20.0;

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
            Float radius = 1.0;
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
            float size = 1.f;
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
                    Float scale = 1.0f;
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
        else if(type == "metal") {
            vec3 color(1.0);
            Float fuzz = 0.0;
            while(!iss.eof()) {
                iss >> header;
                if(header == "color")
                    iss >> color.x >> color.y >> color.z;
                else if(header == "fuzz")
                    iss >> fuzz;
            }
            material = std::make_shared<Metal>(color, fuzz);
        }
        else if(type == "dielectric") {
            vec3 color(1.0);
            float ior = 1.52f;
            while(!iss.eof()) {
                iss >> header;
                if(header == "color")
                    iss >> color.x >> color.y >> color.z;
                else if(header == "ior")
                    iss >> ior;
            }
            material = std::make_shared<Dielectric>(color, ior);
        }
        else if(type == "normal") {
            material = std::make_shared<NormalMat>();
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
        else if(header == "scale") {
            std::vector<float> scale;
            while(true) {
                float s;
                iss >> s;
                if(iss.eof()) break;

                scale.push_back(s);
            }

            if(scale.size() == 1) ts.scale(scale[0]);
            else if(scale.size() == 3) ts.scale(vec3(scale[0], scale[1], scale[2]));
            else THROW("Input value for scale was incorrect!\n");
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
            Float scale = 1.0f;
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
        else if(header == "scale") {
            std::vector<float> scale;
            while(true) {
                float s;
                iss >> s;
                if(iss.eof()) break;

                scale.push_back(s);
            }

            if(scale.size() == 1) ts.scale(scale[0]);
            else if(scale.size() == 3) ts.scale(vec3(scale[0], scale[1], scale[2]));
            else THROW("Input value for scale was incorrect!\n");
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
void Scene::streamProgress(int currentLine, int maxLine, Float elapsedTime, int progressLen) {    
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

    std::cout << "PRIMITIVES: " << this->primitives.size() << std::endl;
    std::cout << "LIGHTS: " << this->lights.size() << std::endl;

    BVHNode bvh_node(this->primitives, 0, this->primitives.size(), 1, BVHNode::SplitMethod::SAH);

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);

    int progress_len = 20;

    auto width = image.second.getWidth();
    auto height = image.second.getHeight();

    #ifdef _OPENMP
    int n_threads = omp_get_max_threads();
    std::cout << "[OpenMP] NUM_THREADS: " << n_threads << std::endl;
    #endif

    for(int y=0; y<height; y++) {
        clock_gettime(CLOCK_REALTIME, &end_time);
        Float sec = end_time.tv_sec - start_time.tv_sec;
        Float nsec = (Float)(end_time.tv_nsec - start_time.tv_nsec) / 1000000000;
        Float elapsed_time = sec + nsec;
        this->streamProgress(y, height, elapsed_time, progress_len);

        #ifdef _OPENMP
        #pragma omp parallel for num_threads(n_threads)
        #endif
        for(int x=0; x<width; x++) {
            vec3 color(0,0,0);
            
            for(int s=0; s<samples_per_pixel; s++) {
                auto u = (x + random_float()) / width;
                auto v = (y + random_float()) / height;

                Ray r = camera.get_ray(u, v);
                color += integrator.trace(r, bvh_node, lights, background, depth);
            }
            RGBA rgb_color = RGBA(vec2color(color, 1.0 / samples_per_pixel), 255);
            image.second.set(x, height-(y+1), rgb_color);
        }
    }

    std::string file_format = split(image.first, '.').back();
    image.second.write(image.first, file_format);
    std::cerr << "\nDone\n";
}

}