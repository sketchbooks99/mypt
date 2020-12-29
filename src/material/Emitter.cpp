#include "Emitter.h"

namespace mypt {

bool Emitter::scatter(const Ray& /* r_in */, HitRecord& /* rec */, ScatterRecord& /* srec */)
{
    return false;
}

vec3 Emitter::emitted(const Ray& /* r_in */, const HitRecord& rec) {
    return albedo->value(rec.u, rec.v, rec.p) * intensity;
}

}