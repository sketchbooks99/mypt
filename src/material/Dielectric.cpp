#include "Dielectric.h"

namespace mypt {

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
    bool into;
    if(dot(r_in.direction(), rec.normal) > 0) {
        into = true;
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    } else {
        into = false;
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    
    float reflect_prob;
    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted, into)) {
        reflect_prob = schlick(cosine, ref_idx);
    } else {
        reflect_prob = 1.0f;
    }
    if(random_double() < reflect_prob) {
        srec.specular_ray = Ray(rec.p, reflected);
    } else {
        srec.specular_ray = Ray(rec.p, refracted);
    }
    return true;
}
}