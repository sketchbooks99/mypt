#pragma once 

#include <vector>
#include "Shape.h"
#include "Material.h"
#include "Ray.h"
#include "Transform.h"
#include "../material/Isotropic.h"

namespace mypt {

class Primitive {
public:
    virtual bool intersect(Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;
};

class ShapePrimitive final : public Primitive {
public:
    ShapePrimitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform)
    : shape(shape), material(material), transform(transform){}
    virtual bool intersect(Ray& r, double t_min, double t_max, HitRecord& rec) const override
    {
        Ray tr_ray = *transform * r;
        if(!shape->intersect(tr_ray, t_min, t_max, rec))
            return false;
        
        auto p = rec.p;
        auto normal = rec.normal;
        p = mat4::point_mul(transform->getMatrix(), rec.p);
        normal = normalize(mat4::normal_mul(transform->getInvMatrix(), rec.normal));

        rec.p = p;
        rec.set_face_normal(r, normal);
        rec.mat_ptr = material;

        return true;
    }
    
    virtual AABB bounding() const override {
        vec3 min(infinity, infinity, infinity);
        vec3 max(-infinity, -infinity, -infinity);

        for(int i=0; i<2; i++) {            // 0: min.x, 1: max.x
            for(int j=0; j<2; j++) {        // 0: min.y, 1: max.y
                for(int k=0; k<2; k++) {    // 0: min.z, 1: max.z
                    auto x = (1-i)*shape->bounding().min().x + i*shape->bounding().max().x;
                    auto y = (1-j)*shape->bounding().min().y + j*shape->bounding().max().y;
                    auto z = (1-k)*shape->bounding().min().z + k*shape->bounding().max().z;
                    
                    vec3 tr_corner = mat4::point_mul(transform->getMatrix(), vec3(x, y, z));
                    for(int l=0; l<3; l++) {
                        min[l] = fmin(min[l], tr_corner[l]);
                        max[l] = fmax(max[l], tr_corner[l]);
                    }
                } 
            }
        }

        return AABB(min, max);
    }
private:
    std::shared_ptr<Material> material;
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Transform> transform;
};

// Constant Medium
class ConstantMedium final : public Primitive {
public: 
    ConstantMedium(std::shared_ptr<Shape> b, double d, std::shared_ptr<Texture> a)
    : boundary(b), 
      neg_inv_density(-1.0/d),
      phase_function(std::make_shared<Isotropic>(a)) {}
    
    ConstantMedium(std::shared_ptr<Shape> b, double d, vec3 c)
    : boundary(b),
      neg_inv_density(-1.0/d),
      phase_function(std::make_shared<Isotropic>(c)){}
    
    bool intersect(Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override {
        return boundary->bounding();
    }
private:
    std::shared_ptr<Shape> boundary;
    std::shared_ptr<Material> phase_function;
    double neg_inv_density;
};

}