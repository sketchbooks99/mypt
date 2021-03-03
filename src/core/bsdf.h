#pragma once

#include "vec3.h"

namespace mypt {

vec3 reflect(const vec3& v, const vec3& n);

bool refract(const vec3& v, const vec3& n, Float ior, vec3& refracted);
vec3 refract(const vec3& v, const vec3& n, Float ior);

/// TODO: Implement ggx or some famous scattering computation.

}