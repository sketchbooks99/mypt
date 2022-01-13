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
    enum class TraceType { PATH };
    explicit Integrator() {}
    explicit Integrator(TraceType type) : type(type) {}
    vec3 trace(
        Ray& r, const BVHNode& bvh_node, std::vector<std::shared_ptr<Primitive>>& lights, const vec3& background, int depth
    ) const;

    /// \brief Check if surface is occluded by the other primitives.
    bool trace_occlusion(Ray& r, const BVHNode& bvh_node, Float t_min, Float t_max) const;
private:
    TraceType type;
};

}