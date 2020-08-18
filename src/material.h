#ifndef Material_h
#define Material_h

#include "Util.h"
#include "Texture.h"

struct Hit_record;

double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

class Material {
    public:
        virtual bool scatter (
            const Ray& r_in, const Hit_record& rec, vec3& attenuation, Ray& scattered
        ) const = 0;
};

class Lambertian : public Material {
    public: 
        Lambertian(shared_ptr<Texture> a) : albedo(a) {}
        virtual bool scatter(
            const Ray& r_in, const Hit_record& rec, vec3& attenuation, Ray& scattered
        ) const {
            vec3 scatter_direction = rec.normal + random_unit_vector();
            scattered = Ray(rec.p, scatter_direction, r_in.time());
            attenuation = albedo->value(rec.u, rec.v, rec.p);
            return true;
        }

    public:
        shared_ptr<Texture> albedo;
};

class Metal : public Material {
    public:
        Metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const Hit_record& rec, vec3& attenuation, Ray& scattered
        ) const  {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public: 
        vec3 albedo;
        double fuzz;
};

class Dielectric : public Material {
    public:
        Dielectric(double ri) : ref_idx(ri) {}

        virtual bool scatter(
            const Ray& r_in, const Hit_record& rec, vec3& attenuation, Ray& scattered
        ) const {
            attenuation = vec3(1.0, 1.0, 1.0);
            double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

            vec3 unit_direction = unit_vector(r_in.direction());
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
        double ref_idx;
};

#endif
