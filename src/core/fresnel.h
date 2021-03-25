#pragma once

#include "vec.h"

namespace mypt {

/** 
 * \ref: http://www.pbr-book.org/3ed-2018/Reflection_Models/Specular_Reflection_and_Transmission.html
 * 
 * \note cos_i should be positive and checking if ray goes into 
 * dielectric surface (is cos_i negative?) is never performed in this function. 
 **/
inline Float fr(Float cos_i, Float ni, Float nt) {
    Float sin_i = sqrt(fmax((Float)0, 1-cos_i*cos_i));
    Float sin_t = ni / nt * sin_i;
    Float cos_t = sqrt(fmax((Float)0, 1-sin_t*sin_t));

    Float r_parl = ((nt * cos_i) - (ni * cos_t)) / 
                   ((nt * cos_i) + (ni * cos_t));
    Float r_perp = ((ni * cos_i) - (nt * cos_t)) / 
                   ((ni * cos_i) + (nt * cos_t));

    return (Float)0.5 * (r_parl*r_parl + r_perp*r_perp);
}

/** Compute fresnel reflactance from cosine and index of refraction */
inline Float fr(Float cos_i, Float ior) {
    auto r0 = (1-ior) / (1+ior);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cos_i),5);
}

/** \ref: https://rayspace.xyz/CG/contents/Disney_principled_BRDF/ */
inline Float fr_schlick(Float cos_i, Float f0) {
    return f0 + (1-f0)*pow((1-cos_i),5);
}
inline Float ft_schlick(Float cos_i, Float f90) {
    return 1 + (f90-1)*pow((1 - cos_i), 5);
}

/** 
 * \ref: https://qiita.com/_Pheema_/items/f1ffb2e38cc766e6e668
 * 
 * @param
 * - n : normal
 * - h : half vector
 * - rough : roughness of the surface. [0,1]
 **/ 
inline Float ggx(const vec3& n, const vec3& h, Float rough) {
    Float d = dot(n, h);
    Float dd = d*d;
    Float a = (1.0 - (1.0-rough*rough)*dd);
    Float denom = pi * a*a;
    return rough*rough / denom;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n) * n;
}

inline vec3 refract(const vec3& v, const vec3& n, Float ior) {
    auto nv = normalize(v);
    auto cos_i = dot(-nv, n);
    
    vec3 r_out_perp = ior * (nv + cos_i*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

/** \ref: https://knzw.tech/raytracing/?page_id=478 */
inline vec3 refract(const vec3& wi, const vec3& n, Float cos_i, Float ni, Float nt) {
    Float nt_ni = nt / ni;
    Float ni_nt = ni / nt;
    Float D = sqrt(nt_ni*nt_ni - (1-cos_i*cos_i)) - cos_i;
    return ni_nt * (wi - D * n);
}

}