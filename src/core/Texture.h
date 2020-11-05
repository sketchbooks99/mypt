#pragma once

#include "Util.h"

class Texture {
    public:
        virtual vec3 value(double u, double v, const vec3& p) const = 0;
};