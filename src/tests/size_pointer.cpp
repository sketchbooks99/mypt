#include <iostream>
#include "../core/MathUtil.h"

using namespace mypt;

enum class MaterialType {
    None, 
    Diffuse, 
    Dielectric, 
    Metal
};

std::ostream& operator<<(std::ostream& out, const MaterialType& type) {
    switch(type) {
    case MaterialType::None:
        return out << "MaterialType::None";
    case MaterialType::Diffuse:
        return out << "MaterialType::Diffuse";
    case MaterialType::Dielectric:
        return out << "MaterialType::Dielectric";
    case MaterialType::Metal:
        return out << "MaterialType::Metal";
    default:
        return out << "";
    }
}

// Abstract class
class Material {    
public:
    virtual MaterialType type() const = 0;
    virtual size_t member_size() const = 0;
};

class Diffuse : public Material {
public:
    Diffuse(vec3 c) : color(c) {}
    MaterialType type() const override { return MaterialType::Diffuse; }
    size_t member_size() const override { return sizeof(color); }
private:
    vec3 color;
};

class Dielectric : public Material {
public:
    Dielectric(vec3 c, float ior) {}
    MaterialType type() const override { return MaterialType::Dielectric; }
    size_t member_size() const override { return sizeof(color) + sizeof(ior); }
private:
    vec3 color;
    float ior;
};

class Metal : public Material {
public:
    Metal(vec3 c, vec3 k, float ior) : color(c), k(k), ior(ior) {}
    MaterialType type() const override { return MaterialType::Metal; }
    size_t member_size() const override { return sizeof(color) + sizeof(k) + sizeof(ior); }
private:
    vec3 color, k;
    float ior;
};

int main(void) {
    std::vector<Material*> matptrs;
    matptrs.push_back(new Diffuse(vec3()));
    matptrs.push_back(new Dielectric(vec3(), 1.5));
    matptrs.push_back(new Metal(vec3(), vec3(), 1.5f));

    std::cout << sizeof(float) << sizeof(double) << sizeof(vec3) << std::endl;

    for (auto& matptr : matptrs) {
        std::cout << matptr->type() << ", sizeof(): " << matptr->member_size() << std::endl;
    } 

    return 0;
}