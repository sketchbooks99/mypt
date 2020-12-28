#pragma once 

#include "Util.h"
#include "Primitive.h"
#include "Material.h"
#include "../render/Camera.h"
#include "../render/Integrator.h"
#include "../core/Image.h"

namespace mypt {

class Scene {
public:
    Scene(const std::string& filename);

    void render();
    void invert_render();

private:
    void createCamera(std::ifstream&, double aspect);

    void createPrimitive(std::ifstream&);

    void createLight(std::ifstream&);

    void streamProgress(int currentLine, int maxLine, double elapsedTime, int progressLen=20);

    std::vector<std::shared_ptr<Primitive>> primitives;
    std::vector<std::shared_ptr<Primitive>> lights;
    Camera camera;
    Integrator integrator;
    Image<RGBA> image;
    Image<RGB> refimage;
    int samples_per_pixel, depth;
    vec3 background;
    std::string image_name;
    TransformSystem ts;
};

}