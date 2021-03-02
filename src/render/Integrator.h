#pragma once

/** Abstract class for several integrators.
 * 
 * TODO:
 *  - Basic implementation
 *  - Bidirectional path tracing
 *  - Metropolis Light transport
 * 
 **/

#include "../core/Material.h"
#include "../core/Ray.h"
#include "../core/BVH.h"
#include "../core/Primitive.h"

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
private:
    TraceType type;
};

}