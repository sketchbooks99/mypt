#pragma once

#include "Util.h"
#include "MathUtil.h"

namespace mypt {

template <typename T>
struct ParamItem;

class Params {
public:
    Params() {}
    
private:
    std::vector<std::shared_ptr<ParamItem<bool>>> bools;
    std::vector<std::shared_ptr<ParamItem<int>>> ints;
    std::vector<std::shared_ptr<ParamItem<float>>> floats;
    std::vector<std::shared_ptr<ParamItem<double>>> doubles;
    std::vector<std::shared_ptr<ParamItem<vec3>>> vec3s;
    std::vector<std::shared_ptr<ParamItem<RGBA>>> rgbas;
    std::vector<std::shared_ptr<ParamItem<RGB>>> rgbs;
    std::vector<std::shared_ptr<ParamItem<std::string>>> strings;
    std::vector<std::shared_ptr<ParamItem<std::string>>> textures;
};

template <typename T>
struct ParamItem {
    const std::string name;
    const std::unique_ptr<T[]> values;
    const int n;
};

}