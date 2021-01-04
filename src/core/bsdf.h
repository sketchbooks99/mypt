#pragma once 

#include "vec3.h"

namespace mypt {

vec3 reflect(const vec3& v, const vec3& n);

bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted);
vec3 refract(const vec3& v, const vec3& n, double ni_over_nt);

vec3 retro_transmit(const vec3& v, const vec3& n);

}