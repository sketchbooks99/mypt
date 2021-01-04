#include "Emitter.h"

namespace mypt {

bool Emitter::scatter(const Ray& /* r_in */, HitRecord& /* rec */, ScatterRecord& /* srec */) const
{
    return false;
}

vec3 Emitter::emitted(const Ray& /* r_in */, const HitRecord& /* rec */, double u, double v, const vec3& p) const {
    return albedo->value(u, v, p) * intensity;
}

}