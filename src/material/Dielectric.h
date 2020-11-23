#pragma once

#include "../core/Material.h"

struct HitRecord;

double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

class Dielectric final : public Material {
    public:
        Dielectric(double ri) : albedo(vec3(1.0f)), ref_idx(ri) {}
        Dielectric(vec3 a, double ri) : albedo(a), ref_idx(ri) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
        ) const {
            attenuation = albedo;
            double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

            vec3 unit_direction = normalize(r_in.direction());
            double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
            if(etai_over_etat * sin_theta > 1.0) {
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = Ray(rec.p, reflected);
                return true;
            }
            double reflect_prob = schlick(cos_theta, etai_over_etat);
            if(random_double() < reflect_prob) {
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = Ray(rec.p, reflected);
                return true;
            }
            vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
            scattered = Ray(rec.p, refracted);
            return true;
        }

    public:
        vec3 albedo;
        double ref_idx;
};
