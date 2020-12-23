#include "Dielectric.h"

namespace mypt {

/* 
bool Dielectric::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const  {
    srec.is_specular = true;
    srec.pdf = 0;
    srec.attenuation = albedo;
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    vec3 refracted;
    float ni_over_nt;
    float cosine;
    if(dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    
    float reflect_prob;
    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    } else {
        reflect_prob = 1.0;
    }
    if(random_double() < reflect_prob) {
        srec.specular_ray = Ray(rec.p, reflected);
    } else {
        srec.specular_ray = Ray(rec.p, refracted);
    }
    return true;
} 
*/

bool Dielectric::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const  {
    srec.is_specular = true;
    srec.pdf = 0;
    srec.attenuation = albedo;
    bool into = dot(r_in.direction(), rec.normal) > 0;
    float ni_over_nt = into ? ref_idx : 1.0 / ref_idx;
    
    auto normalize_direction = normalize(r_in.direction());
    float cosine = fmin(dot(-normalize_direction, rec.normal), 1.0);
    float sine = sqrt(1.0 - cosine*cosine);

    bool cannot_refract = ni_over_nt * sine > 1.0;
    float reflect_prob = schlick(cosine, ni_over_nt);
    if(cannot_refract || reflect_prob > random_double())
        srec.specular_ray = Ray(rec.p, reflect(normalize_direction, rec.normal));
    else
        srec.specular_ray = Ray(rec.p, refract(normalize_direction, rec.normal, ni_over_nt));
    return true;
}

}