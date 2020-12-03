#pragma once 

#include <vector>
#include "Shape.h"
#include "Material.h"
#include "Ray.h"
#include "Transform.h"

class Primitive {
public:
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
};

class ShapePrimitive final : public Primitive {
public:
    ShapePrimitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform)
    : shape(shape), material(material), transform(transform){}
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
    {
        Ray tr_ray = *transform * r;
        if(!shape->intersect(tr_ray, t_min, t_max, rec)) 
            return false;

        auto normal = mat4::vector_mul(transform->getMatrix(), rec.normal);
        rec.set_face_normal(tr_ray, normal);
        rec.p = mat4::point_mul(transform->getMatrix(), rec.p);
        rec.mat_ptr = material;

        return true;
    }
    
    virtual AABB bounding() const override {
        return shape->bounding();
    }
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Transform> transform;
};
