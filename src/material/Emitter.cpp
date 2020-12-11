#include "Emitter.h"

namespace mypt {

bool Emitter::scatter(const Ray& r_in, HitRecord& rec, vec3 &attenuation, Ray& scattered, double& pdf) const
{
    return false;
}

vec3 Emitter::emitted(double u, double v, const vec3& p) const {
    return albedo->value(u, v, p) * intensity;
}

}