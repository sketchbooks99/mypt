#pragma once

#include "../core/Primitive.h"
#include "../core/Texture.h"
#include "../material/Isotropic.h"

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
    
    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override {
        return boundary->bounding();
    }
private:
    std::shared_ptr<Shape> boundary;
    std::shared_ptr<Material> phase_function;
    double neg_inv_density;
};