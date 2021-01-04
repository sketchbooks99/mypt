#include "Integrator.h"
#include "../core/PDF.h"

namespace mypt {

vec3 Integrator::trace(
    const Ray& r, const BVH& bvh, std::vector<std::shared_ptr<Primitive>>& lights, const vec3& background, int depth
) const {
    HitRecord rec;
    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if(depth <= 0)
        return vec3(0.0, 0.0, 0.0);

    if(!bvh.intersect(r, eps, infinity, rec))
        return background;

    ScatterRecord srec;
    vec3 emitted = rec.mat_ptr->emitted(r, rec);
    if(!rec.mat_ptr->scatter(r, rec, srec))
        return emitted;

    if(srec.is_specular) {
        return srec.attenuation
            * trace(srec.scattered, bvh, lights, background, depth-1);
    }

    auto light_ptr = std::make_shared<LightPDF>(lights, rec.p);
    MixturePDF p(light_ptr, srec.pdf);

    Ray scattered = Ray(rec.p, p.generate(), r.time(), r.color());
    auto pdf = p.value(scattered.direction());
    
    return emitted
         + srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                  * trace(scattered, bvh, lights, background, depth-1) / pdf;
}

void Integrator::propagate(const Ray& r, const BVH& bvh, int depth) {
    HitRecord rec;
    if(depth <= 0)
        return;
    if(!bvh.intersect(r, eps, infinity, rec))
        return;
    ScatterRecord srec;
    if(!rec.mat_ptr->scatter(r, rec, srec))
        return;
    
    Ray scattered = srec.scattered;
    propagate(scattered, bvh, depth-1);
}

}