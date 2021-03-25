#include "emitter.h"

namespace mypt {

bool Emitter::scatter(const Ray& /* r_in */, SurfaceInteraction& /* si */) const
{
    return false;
}

vec3 Emitter::emitted(const Ray& /* r_in */, const SurfaceInteraction& si) const {
    return albedo->value(si.uv, si.p) * intensity;
}

}