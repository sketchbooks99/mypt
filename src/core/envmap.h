#include "vec.h"
#include "ray.h"
#include "image.h"
#include "util.h"
#include "../texture/image.h"

namespace mypt {

class Envmap {
public:
    virtual vec3 eval(const Ray& r) const = 0;
};

class ConstantEnvmap final : public Envmap {
public:
    ConstantEnvmap(const vec3& c);
    vec3 eval(const Ray& r) const override;
private:
    vec3 color;
};

class ImageEnvmap final : public Envmap {
public:
    ImageEnvmap(const std::filesystem::path& filepath);

    vec3 eval(const Ray& r) const override;

    void load(const std::filesystem::path& filepath);
private:
    ImageTexture texture;
};

}