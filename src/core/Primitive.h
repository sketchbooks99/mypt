#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Util.h"
#include "Shape.h"
#include "Material.h"

class Primitive {
public:
    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
    AABB bounding() const;
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
};

AABB Primitive::bounding() const {
    return shape->bounding();
}

#endif
