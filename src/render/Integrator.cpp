#include "Integrator.h"
#include "../core/PDF.h"

namespace mypt {

vec3 Integrator::trace(
    Ray& r, const BVH& bvh, std::shared_ptr<Primitive>& lights, const vec3& background, int depth
) const {
    HitRecord rec;
    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if(depth <= 0)
        return vec3(0.0, 0.0, 0.0);

    if(!bvh.intersect(r, 0, infinity, rec))
        return background;

    ScatterRecord srec;
    // vec3 attenuation;
    vec3 emitted = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);

    if(!rec.mat_ptr->scatter(r, rec, srec))
        return emitted;

    PrimitivePDF light_pdf(lights, rec.p);
    Ray scattered = Ray(rec.p, light_pdf.generate(), r.time());
    auto pdf = light_pdf.value(scattered.direction());
    
    return emitted
         + srec.attenuation * rec.mat_ptr->scattering_pdf(r, rec, scattered)
                  * trace(scattered, bvh, lights, background, depth-1) / pdf;
}

}