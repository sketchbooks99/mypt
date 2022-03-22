#pragma once 

#include "util.h"
#include "primitive.h"
#include "material.h"
#include "../render/camera.h"
#include "../render/integrator.h"
#include "../core/image.h"
#include <omp.h>

namespace mypt {

class Scene {
public:
    explicit Scene(const std::string& filename);
    void render();

private:
    // Parse scene configuration and create objects.
    void createCamera(std::ifstream&, Float aspect);
    void createShapes(std::istringstream&, std::vector<std::shared_ptr<Shape>>&);
    auto createMaterial(std::istringstream&);
    void createPrimitive(std::ifstream&);
    void createLight(std::ifstream&);
    // Stream rendering progress to standard out stream.
    void streamProgress(int currentLine, int maxLine, Float elapsedTime, int progressLen=20);

    std::vector<std::shared_ptr<Primitive>> primitives;
    std::vector<std::shared_ptr<Primitive>> lights;
    Camera camera;
    std::unique_ptr<Integrator> integrator;
    std::pair<std::string, Image<RGBA>> image;
    int samples_per_pixel, depth;
    vec3 background;
    TransformSystem ts;
};

}