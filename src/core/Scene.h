#pragma once 

#include "Util.h"
#include "Primitive.h"
#include "Material.h"
#include "../render/Camera.h"
#include "../render/Integrator.h"
#include "../core/Image.h"
#include <omp.h>

namespace mypt {

class Scene {
public:
    Scene(const std::string& filename);
    void render();

private:
    // Parse scene configuration and create objects.
    void createCamera(std::ifstream&, double aspect);
    void createShapes(std::istringstream&, std::vector<std::shared_ptr<Shape>>&);
    auto createMaterial(std::istringstream&);
    void createPrimitive(std::ifstream&);
    void createLight(std::ifstream&);
    // Stream rendering progress to standard out stream.
    void streamProgress(int currentLine, int maxLine, double elapsedTime, int progressLen=20);

    std::vector<std::shared_ptr<Primitive>> primitives;
    std::vector<std::shared_ptr<Primitive>> lights;
    Camera camera;
    Integrator integrator;
    Image<RGBA> image;
    Image<RGBA> refimage;
    std::shared_ptr<Image<RGBA>> absorbed_image;
    int samples_per_pixel, depth;
    vec3 background;
    std::string image_name;
    TransformSystem ts;
};

}