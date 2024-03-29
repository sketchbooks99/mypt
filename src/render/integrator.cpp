#include "integrator.h"
#include "../core/pdf.h"

namespace mypt {

/** 
 * \todo 
 * - Recursive tracing is not good at implementaion of next event estimation.
 * 
 * - Terminating ray tracing when ray intersect with an emitter will result in incorrect result
 *   because the contribution from background color will be not reflected.
 */

vec3 PathIntegrator::trace(
    const Ray& r, const BVHNode& bvh_node, 
    const std::vector<std::shared_ptr<Primitive>>& lights, 
    const vec3& background, int depth) const 
{
    SurfaceInteraction si;
    if(depth <= 0)
        return vec3(0.0f);

    if(!bvh_node.intersect(r, eps, infinity, si))
        return background;

    vec3 emitted = si.mat_ptr->emitted(r, si);
    if(!si.mat_ptr->scatter(r, si))
        return emitted;

    if(si.is_specular) {
        return si.attenuation
            * trace(si.scattered, bvh_node, lights, background, depth-1);
    } 

    std::shared_ptr<PDF> pdf_ptr;
    if (lights.size() > 0) {
        auto light_ptr = std::make_shared<LightPDF>(lights, si.p);
        pdf_ptr = std::make_shared<MixturePDF>(light_ptr, si.pdf_ptr);
    } else {
        pdf_ptr = std::make_shared<CosinePDF>(si.n);
    }
    si.scattered = Ray(si.p, pdf_ptr->generate(), r.time());
    auto pdf = pdf_ptr->value(si.scattered.direction());

    /// \todo NEE: Launch shadow ray from diffuse surface to lights.

    if(pdf > 0) {
        return emitted
            + si.attenuation * si.mat_ptr->scattering_pdf(r, si)
                * trace(si.scattered, bvh_node, lights, background, depth-1) / pdf;
    } else {
        return emitted;
    }
}

/** \todo This implementation still don't release correct result. */
// vec3 Integrator::trace(
//     Ray& r, const BVHNode& bvh_node, std::vector<std::shared_ptr<Primitive>>& lights, const vec3& background, int depth
// ) const {
//     vec3 result;
//     for (int i = 0; i < depth; i++) {
//         SurfaceInteraction si;
//         vec3 radiance; 
//         vec3 emission;
//         si.attenuation = vec3(1.0);

//         if (!bvh_node.intersect(r, eps, infinity, si)) {
//             result += background * si.attenuation;
//             break;
//         }

//         emission = si.mat_ptr->emitted(r, si);
//         if (!si.mat_ptr->scatter(r, si)) {
//             break;
//         }

//         Float pdf = 1.0f;
//         if (!si.is_specular) {
//             auto light_ptr = std::make_shared<LightPDF>(lights, si.p);
//             MixturePDF p(light_ptr, si.pdf_ptr);
//             si.scattered = Ray(si.p, p.generate(), r.time());
//             pdf = p.value(si.scattered.direction());
//         }

//         // rendering equation
//         result += emission;
//         result += si.attenuation * si.mat_ptr->scattering_pdf(r, si) * radiance / pdf;

//         r = si.scattered;
//     }
//     return result;
// }

bool PathIntegrator::trace_shadow(const Ray& r, const BVHNode& bvh_node, Float tmin, Float tmax) const 
{
    SurfaceInteraction si;
    return bvh_node.intersect(r, tmin, tmax, si);
}

vec3 BiPathIntegrator::trace(
    const Ray& r, const BVHNode& bvh_node, 
    const std::vector<std::shared_ptr<Primitive>>& lights, 
    const vec3& background, int depth) const 
{

}

}