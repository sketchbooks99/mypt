#pragma once 

#include <vector>
#include "Shape.h"
#include "Material.h"
#include "Ray.h"
#include "Transform.h"
#include "../material/Isotropic.h"

namespace mypt {

enum class PrimitiveType {
    None,
    ShapePrimitive,
    ConstantMedium, 
    BVHNode
};

inline std::ostream& operator<<(std::ostream& out, const PrimitiveType& type) {
    switch (type) {
    case PrimitiveType::ShapePrimitive:
        return out << "PrimitiveType::ShapePrimitive";
    case PrimitiveType::ConstantMedium:
        return out << "PrimitiveType::ConstantMedium";
    case PrimitiveType::BVHNode:
        return out << "PrimitiveType::BVHNode";
    default:
        return out << "";
    }
}

class Primitive {
public:
    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual AABB bounding() const = 0;

    virtual double pdf_value(const vec3& /* o */, const vec3& /* v */) const { return 0.0; }
    virtual vec3 random(const vec3& /* o */) const { return vec3(1, 0, 0); }

    virtual PrimitiveType type() const = 0;
};

class ShapePrimitive final : public Primitive {
public:
    ShapePrimitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform);
    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override;

    double pdf_value(const vec3& o, const vec3& v) const override;
    vec3 random(const vec3& o) const override;

    PrimitiveType type() const override { return PrimitiveType::ShapePrimitive; }
    MatType mattype() const { return material->type(); }
    ShapeType shapetype() const { return shape->type(); }
private:
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Material> material;
    std::shared_ptr<Transform> transform;
    AABB bbox;
};

// Constant Medium
class ConstantMedium final : public Primitive {
public: 
    ConstantMedium(std::shared_ptr<Shape> b, std::shared_ptr<Texture> a, double d)
    : boundary(b), 
      phase_function(std::make_shared<Isotropic>(a)), 
      neg_inv_density(-1.0/d) {}
    
    ConstantMedium(std::shared_ptr<Shape> b, vec3 c, double d)
    : boundary(b),
      phase_function(std::make_shared<Isotropic>(c)), 
      neg_inv_density(-1.0/d) {}
    
    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override {
        return boundary->bounding();
    }

    PrimitiveType type() const override { return PrimitiveType::ConstantMedium; }
private:
    std::shared_ptr<Shape> boundary;
    std::shared_ptr<Material> phase_function;
    double neg_inv_density;
};

}