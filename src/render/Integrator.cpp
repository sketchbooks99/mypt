#include "Integrator.h"
#include "../core/PDF.h"

namespace mypt {

vec3 Integrator::trace(
    Ray& r, const BVHNode& bvh_node, std::vector<std::shared_ptr<Primitive>>& lights, const vec3& background, int depth
) const {
    HitRecord rec;
    if(depth <= 0)
        return vec3(0.0, 0.0, 0.0);

    if(!bvh_node.intersect(r, eps, infinity, rec))
        return background;

    ScatterRecord srec;
    vec3 emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
    if(!rec.mat_ptr->scatter(r, rec, srec))
        return emitted;

    if(srec.is_specular) {
        return srec.attenuation
            * trace(srec.specular_ray, bvh_node, lights, background, depth-1);
    } 

    auto light_ptr = std::make_shared<LightPDF>(lights, rec.p);
    MixturePDF p(light_ptr, srec.pdf);

    Ray scattered = Ray(rec.p, p.generate(), r.time());
    auto pdf = p.value(scattered.direction());

    if(pdf > 0) {
        return emitted
            + srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                * trace(scattered, bvh_node, lights, background, depth-1) / pdf;
    } else {
        return emitted;
    }
}

}