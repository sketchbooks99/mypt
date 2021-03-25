#pragma once 

#include <vector>
#include <typeinfo>
#include "shape.h"
#include "material.h"
#include "ray.h"
#include "transform.h"
#include "../material/isotropic.h"

namespace mypt {

enum class PrimitiveType {
    None,           // Abstract class
    ShapePrimitive,
    ConstantMedium, 
    BVHNode
};

inline std::ostream& operator<<(std::ostream& out, PrimitiveType type) {
    switch(type) {
    case PrimitiveType::None:
        return out << "PrimitiveType::None";
        break;
    case PrimitiveType::ShapePrimitive:
        return out << "PrimitiveType::ShapePrimitive";
        break;
    case PrimitiveType::ConstantMedium:
        return out << "PrimitiveType::ConstantMedium";
        break;
    case PrimitiveType::BVHNode:
        return out << "PrimitiveType::BVHNode";
        break;
    default:
        Throw("This PrimitiveType doesn't exist.");
        break;
    }
}

// -------------------------------------------------------------------------------------
class Primitive {
public:
    virtual bool intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const = 0;
    virtual AABB bounding() const = 0;

    // Compute pdf value of primitive
    virtual Float pdf_value(const vec3& /* o */, const vec3& /* v */) const { return 0.0; }
    // Compute outward direction at origin o
    virtual vec3 random(const vec3& /* o */) const { return vec3(1, 0, 0); }

    virtual PrimitiveType type() const = 0;

    virtual std::string to_string() const = 0;
};

// -------------------------------------------------------------------------------------
/** \brief ShapePrimitive class store a shape, material, and transform informations.
 *  In intersection test, stored transformation is applied to incident rays. */
class ShapePrimitive final : public Primitive {
public:
    ShapePrimitive(std::shared_ptr<Shape> shape, std::shared_ptr<Material> material, std::shared_ptr<Transform> transform);
    
    bool intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const override;
    AABB bounding() const override;

    Float pdf_value(const vec3& o, const vec3& v) const override;
    vec3 random(const vec3& o) const override;

    PrimitiveType type() const override { return PrimitiveType::ShapePrimitive; }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "ShapePrimitive : {" << std::endl;
        oss << "\tShape : " << shape->to_string() << std::endl;
        oss << "\tMaterial : " << material->to_string() << std::endl;
        oss << "}";
        return oss.str();
    }
private:
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Material> material;
    std::shared_ptr<Transform> transform;
    AABB bbox;
};

// -------------------------------------------------------------------------------------
/** \brief Medium with boundary which is determined by shape object.
 *  Scattering and Absorption properties are computed by density of medium */
class ConstantMedium final : public Primitive {
public: 
    ConstantMedium(std::shared_ptr<Shape> b, std::shared_ptr<Texture> a, Float d)
    : boundary(b), 
      phase_function(std::make_shared<Isotropic>(a)), 
      neg_inv_density(-1.0/d) {}
    
    ConstantMedium(std::shared_ptr<Shape> b, vec3 c, Float d)
    : boundary(b),
      phase_function(std::make_shared<Isotropic>(c)), 
      neg_inv_density(-1.0/d) {}
    
    bool intersect(const Ray& r, Float t_min, Float t_max, SurfaceInteraction& si) const override;
    AABB bounding() const override {
        return boundary->bounding();
    }

    PrimitiveType type() const override { return PrimitiveType::ConstantMedium; }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "ShapePrimitive : {" << std::endl;
        oss << "\tBoundary : " << boundary->to_string() << "," << std::endl;
        oss << "\tPhase Function : " << phase_function->to_string() << "," << std::endl;
        oss << "\tDensity : " << neg_inv_density << std::endl;
        oss << "}";
        return oss.str();
    }
private:
    std::shared_ptr<Shape> boundary;
    std::shared_ptr<Material> phase_function;
    Float neg_inv_density;
};

}