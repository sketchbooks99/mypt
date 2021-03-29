#include "vec.h"
#include "image.h"

namespace mypt {

class Envmap {
    virtual vec3 eval() const = 0;
};

class ConstantEnvmap final : public Envmap {

private:
    vec3 color;
};

class ImageEnvmap final : public Envmap {
    ImageEnvmap() {}
};

}