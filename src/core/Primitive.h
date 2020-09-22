#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include "Util.h"
#include "Shape.h"
#include "Material.h"

class Primitive {
public:
    Primitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material)
    : shape(shape), material(material){}
    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
    AABB bounding() const;
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
};

bool Primitive::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    if(!shape->intersect(r, t_min, t_max, rec)) 
        return false;

    rec.mat_ptr = material;

    return true;
}

AABB Primitive::bounding() const {
    return shape->bounding();
}

#endif
