#ifndef CONSTANT_H
#define CONSTANT_H

#include "../core/Texture.h"

class ConstantTexture : public Texture {
    public:
        ConstantTexture(){}
        ConstantTexture(vec3 c) : color(c) {}

        virtual vec3 value(double u, double v, const vec3& p) const {
            return color;
        }

    public:
        vec3 color;
};

#endif