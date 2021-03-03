#pragma once

#include "math_util.h"

namespace mypt {

inline Float trilinear_interp(Float c[2][2][2], Float u, Float v, Float w) {
    auto accum = 0.0;
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            for(int k=0; k<2; k++) {
                accum += (i*u + (1-i)*(1-u))*
                         (j*v + (1-j)*(1-v))*
                         (k*w + (1-k)*(1-w))*c[i][j][k];
            }
        }
    }
    return accum;
}

inline Float perlin_interp(vec3 c[2][2][2], Float u, Float v, Float w) {
    auto uu = u*u*(3-2*u);
    auto vv = v*v*(3-2*v);
    auto ww = w*w*(3-2*w);
    auto accum = 0.0;

    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            for(int k=0; k<2; k++) {
                vec3 weight_v(u-i, v-j, w-k);
                accum += (i*uu + (1-i) * (1-uu))
                        * (j*vv + (1-j) * (1-vv))
                        * (k*ww + (1-k) * (1-ww))
                        * dot(c[i][j][k], weight_v);
            }
        }
    }
    return accum;
}

class Perlin {
public:
    Perlin();
    ~Perlin();

    Float turb(const vec3& p, int depth=7) const;
    Float noise(const vec3& p) const;

private:
    static const int point_count = 256;
    vec3* ranvec;
    int* perm_x;
    int* perm_y;
    int* perm_z;

    static int* perlin_generate_perm() {
        auto p = new int[point_count];

        for(int i = 0; i < Perlin::point_count; i++) {
            p[i] = i;
        }

        permute(p, point_count);

        return p;
    }

    static void permute(int *p, int n) {
        for(int i = n-1; i>0; i--) {
            int target = random_int(0,i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }
};

}