#pragma once

#include "../core/Ray.h"

namespace mypt {

class Camera {
public: 
    Camera() {}
    Camera(
        vec3 lookfrom, vec3 lookat, vec3 vup,
        Float vfov, // top to botton, in degrees
        Float aspect, Float aperture, Float focus_dist, Float t0 = 0, Float t1 = 0
    );

    Ray get_ray(Float s, Float t);

public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    Float lens_radius;
    Float time0, time1; // shutter open/close times
};

}

