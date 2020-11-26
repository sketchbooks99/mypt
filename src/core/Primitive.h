#pragma once 

#include <vector>
#include "Shape.h"
#include "Material.h"
#include "Ray.h"

class Primitive {
public:
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
};

class ShapePrimitive final : public Primitive {
public:
    ShapePrimitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material)
    : shape(shape), material(material){}
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
    {
        if(!shape->intersect(r, t_min, t_max, rec)) 
            return false;

        rec.mat_ptr = material;

        return true;
    }
    
    virtual AABB bounding() const override {
        return shape->bounding();
    }
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
};
