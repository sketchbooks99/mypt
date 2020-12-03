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
        // std::cout << "Ray: " << r.origin() << ", " << r.direction() << std::endl;
        // std::cout << "Ray_: " << tr_ray.origin() << ", " << tr_ray.direction() << std::endl;
        if(!shape->intersect(tr_ray, t_min, t_max, rec)) 
            return false;
        
        auto p = rec.p;
        auto normal = rec.normal;
        p = mat4::point_mul(transform->getMatrix(), p);
        normal = mat4::vector_mul(transform->getMatrix(), normal);

        rec.p = p;
        rec.set_face_normal(tr_ray, normal);
        rec.mat_ptr = material;

        return true;
    }
    
    // TODO: verify the pointer of ...
    virtual AABB bounding() const override {
        vec3 min(infinity, infinity, infinity);
        vec3 max(-infinity, -infinity, -infinity);

        std::cout << "----------" << std::endl;
        for(int i=0; i<2; i++) {            // 0: min.x, 1: max.x
            for(int j=0; j<2; j++) {        // 0: min.y, 1: max.y
                for(int k=0; k<2; k++) {    // 0: min.z, 1: max.z
                    auto x = (i-1)*shape->bounding().min().x + i*shape->bounding().max().x;
                    auto y = (j-1)*shape->bounding().min().y + j*shape->bounding().max().y;
                    auto z = (k-1)*shape->bounding().min().z + k*shape->bounding().max().z;

                    // Update min, and bounding box by transformed vector
                    // auto tr_corner = mat4::point_mul(transform->getMatrix(), vec3(x, y, z));
                    vec3 tr_corner(x, y, z);
                    std::cout << tr_corner << std::endl;
                    for(int l=0; l<3; l++) {
                        min[l] = fmin(min[l], tr_corner[l]);
                        max[l] = fmax(max[l], tr_corner[l]);
                    }
                } 
            }
        }
        std::cout << "----------" << std::endl;

        return AABB(min, max);
    }
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Transform> transform;
};
