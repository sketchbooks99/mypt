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

class Integrator {
public:
    enum class Type { PATH };
    Integrator() {}
    Integrator(Type type) : type(type) {}
    vec3 trace(
        Ray& r, const BVH& bvh, std::shared_ptr<Primitive>& lights, const vec3& background, int depth
    ) const;
private:
    Type type;
};

}