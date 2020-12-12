#pragma once 

#include <vector>
#include <typeinfo>
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

    virtual double pdf_value(const vec3& o, const vec3& v) const { return 0.0; }
    virtual vec3 random(const vec3& o) const { return vec3(1, 0, 0); }
};

class ShapePrimitive final : public Primitive {
public:
    ShapePrimitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform)
    : shape(shape), material(material), transform(transform){}
    bool intersect(Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override;

    double pdf_value(const vec3& o, const vec3& v) const override;
    vec3 random(const vec3& o) const override;

    const std::type_info &getMatType() { return typeid(material); }
    const std::type_info &getShapeType() { return typeid(shape); }
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