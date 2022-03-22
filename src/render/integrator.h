#pragma once

/** Abstract class for several integrators.
 * 
 * \todo
 *  - [x] Basic implementation
 *  - [ ] Bidirectional path tracing
 *  - [ ] Metropolis Light transport
 * 
 **/

#include "../core/material.h"
#include "../core/ray.h"
#include "../core/bvh.h"
#include "../core/primitive.h"

namespace mypt {

class LightPDF;

class Integrator {
public:
    Integrator() = default;
    virtual vec3 trace(
        const Ray& r, const BVHNode& bvh_node, 
        const std::vector<std::shared_ptr<Primitive>>& lights, 
        const vec3& background, int depth
    ) const = 0;
};

class PathIntegrator : public Integrator {
public:
    PathIntegrator() {}
    vec3 trace(
        const Ray& r, const BVHNode& bvh_node, 
        const std::vector<std::shared_ptr<Primitive>>& lights, 
        const vec3& background, int depth
    ) const override;

    bool trace_shadow(const Ray& r, const BVHNode& bvh_node, Float tmin, Float tmax) const;
};

class BiPathIntegrator : public Integrator {
public:
    BiPathIntegrator() {}

    vec3 trace(
        const Ray& r, const BVHNode& bvh_node, 
        const std::vector<std::shared_ptr<Primitive>>& lights, 
        const vec3& background, int depth
    ) const override;
};

}