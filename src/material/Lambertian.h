#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "../core/Material.h"
#include "../core/Texture.h"

class Lambertian : public Material {
    public: 
        Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}
        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered
        ) const {
            vec3 scatter_direction = rec.normal + random_unit_vector();
            scattered = Ray(rec.p, scatter_direction, r_in.time());
            attenuation = albedo->value(rec.u, rec.v, rec.p);
            return true;
        }

    public:
        std::shared_ptr<Texture> albedo;
};

#endif
