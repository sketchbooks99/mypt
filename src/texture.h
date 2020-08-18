#ifndef Texture_h
#define Texture_h

#include "Util.h"
#include "Perlin.h"

class Texture {
    public:
        virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

class Constant_texture : public Texture {
    public:
        Constant_texture(){}
        Constant_texture(vec3 c) : color(c) {}

        virtual vec3 value(double u, double v, const vec3& p) const {
            return color;
        }

    public:
        vec3 color;
};

class Checker_texture : public Texture {
    public:
        Checker_texture() {}
        Checker_texture(shared_ptr<Texture> t0, shared_ptr<Texture> t1) : even(t0), odd(t1) {}

        virtual vec3 value(double u, double v, const vec3& p) const {
            auto sines = sin(10*p.x) * sin(10*p.y) * sin(10 * p.z);
            if(sines < 0) 
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
        }
        
    public:
        shared_ptr<Texture> odd;
        shared_ptr<Texture> even;
};

class Noise_texture : public Texture {
    public:
        Noise_texture() {}
        Noise_texture(double sc) : scale(sc) {}

        virtual vec3 value(double u, double v, const vec3& p) const {
            return vec3(1,1,1) * 0.5 * (1 + sin(scale * p.z + 10 * noise.turb(p)));
        }
    public:
        Perlin noise;
        double scale;
};

#endif