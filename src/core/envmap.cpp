#include "envmap.h"

namespace mypt {

    static bool intersectEnvmap(const Ray& r, const Float& max_distance = 1e8f)
    {
        
    }

    ConstantEnvmap::ConstantEnvmap(const vec3& c)
        : color(c)
    {

    }

    vec3 ConstantEnvmap::eval(const Ray& r) const
    {

    }

    ImageEnvmap(const std::filesystem::path& filepath)
    {
        this->load(filepath);
    }

    vec3 ImageEnvmap::eval(const Ray& r) const 
    {

    }

    void ImageEnvmap::load(const std::filesystem::path& filepath)
    {
        texture = ImageTexture(filepath.string());
    }

} // namespace mypt