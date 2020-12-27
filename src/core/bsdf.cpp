#include "bsdf.h"

namespace mypt {

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n) * n;
}

bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted) {
    vec3 uv = normalize(v);
    float dt = dot(v, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1.0-dt*dt);
    if(discriminant > 0) {
        refracted = ni_over_nt*(uv-n*dt) - n*sqrt(discriminant);
        // refracted = normalize(v * ni_over_nt - n * (dt * ni_over_nt + sqrt(discriminant)));
        return true;
    }
        return false;
}

// ref: https://knzw.tech/raytracing/?page_id=478
vec3 refract(const vec3& v, const vec3& n, double ni_over_nt) {
    #if 0
    auto nv = normalize(v);
    auto cosine = dot(-nv, n);
    auto nt_over_ni = 1.0 / ni_over_nt;
    auto cos2t = nt_over_ni*nt_over_ni - (1.0-cosine*cosine);
    return ni_over_nt*(nv - (sqrt(cos2t)-cosine)*n);

    #else
    auto cosine = fmin(dot(-v, n), 1.0);
    vec3 r_out_perp = ni_over_nt * (v + cosine*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;

    #endif 
}

}