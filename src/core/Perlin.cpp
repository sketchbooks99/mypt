#include "Perlin.h"

Perlin::Perlin() {
    ranvec = new vec3[point_count];
    for(int i = 0; i < point_count; i++) {
        ranvec[i] = normalize(vec3::random(-1, 1));
    }

    perm_x = perlin_generate_perm();
    perm_y = perlin_generate_perm();
    perm_z = perlin_generate_perm();
}

Perlin::~Perlin() {
    delete[] ranvec;
    delete[] perm_x;
    delete[] perm_y;
    delete[] perm_z;
}

double Perlin::turb(const vec3& p, int depth) const {
    auto accum = 0.0;
    vec3 temp_p = p;
    auto weight = 1.0;

    for(int i=0; i<depth; i++) {
        accum += weight*noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum);
}

double Perlin::noise(const vec3& p) const {
    auto u = p.x - floor(p.x);
    auto v = p.y - floor(p.y);
    auto w = p.z - floor(p.z);
    // u = u*u*(3-2*u);
    // v = v*v*(3-2*v);
    // w = w*w*(3-2*w);

    int i = static_cast<int>(floor(p.x));
    int j = static_cast<int>(floor(p.y));
    int k = static_cast<int>(floor(p.z));
    vec3 c[2][2][2];

    for(int di=0; di<2; di++) {
        for(int dj=0; dj<2; dj++) {
            for(int dk=0; dk<2; dk++) {
                c[di][dj][dk] = ranvec[
                    perm_x[(i+di) & 255] ^ 
                    perm_y[(j+dj) & 255] ^ 
                    perm_z[(k+dk) & 255]
                ];
            }
        }
    }
    return perlin_interp(c, u, v, w);
}