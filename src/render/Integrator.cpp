#include "integrator.h"
#include "../core/pdf.h"

namespace mypt {

/** TODO: 
 * Recursive tracing is not good at implementaion of next event estimation.
 */

vec3 Integrator::trace(
    Ray& r, const BVHNode& bvh_node, std::vector<std::shared_ptr<Primitive>>& lights, const vec3& background, int depth
) const {
    SurfaceInteraction si;
    if(depth <= 0)
        return vec3(0.0, 0.0, 0.0);

    if(!bvh_node.intersect(r, eps, infinity, si))
        return background;

    vec3 emitted = si.mat_ptr->emitted(r, si);
    if(!si.mat_ptr->scatter(r, si))
        return emitted;

    if(si.is_specular) {
        return si.attenuation
            * trace(si.scattered, bvh_node, lights, background, depth-1);
    } 

    auto light_ptr = std::make_shared<LightPDF>(lights, si.p);
    MixturePDF p(light_ptr, si.pdf_ptr);
    si.scattered = Ray(si.p, p.generate(), r.time());
    auto pdf = p.value(si.scattered.direction());

    /// TODO: Launch shadow ray from diffuse surface to lights.

    if(pdf > 0) {
        return emitted
            + si.attenuation * si.mat_ptr->scattering_pdf(r, si)
                * trace(si.scattered, bvh_node, lights, background, depth-1) / pdf;
    } else {
        return emitted;
    }
}

/** TODO: This implementation still don't release correct result. */
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

bool Integrator::trace_occlusion(Ray& r, const BVHNode& bvh_node, Float t_min, Float t_max) const {
    SurfaceInteraction si;
    return bvh_node.intersect(r, t_min, t_max, si);
}

}