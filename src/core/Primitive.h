#pragma once 

#include <vector>
#include "Util.h"
#include "Shape.h"
#include "Material.h"

class Primitive {
public:
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
};

class ShapePrimitive : public Primitive{
public:
    ShapePrimitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material)
    : shape(shape), material(material){}
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
    virtual AABB bounding() const;
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
};

bool ShapePrimitive::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    if(!shape->intersect(r, t_min, t_max, rec)) 
        return false;

    rec.mat_ptr = material;

    return true;
}

AABB ShapePrimitive::bounding() const {
    return shape->bounding();
}

