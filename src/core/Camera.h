#pragma once

#include "Ray.h"

class Camera {
    public: 
        Camera(
            vec3 lookfrom, vec3 lookat, vec3 vup,
            double vfov, // top to botton, in degrees
            double aspect, double aperture, double focus_dist, double t0 = 0, double t1 = 0
        );

        Ray get_ray(double s, double t);
    
    public:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
        double time0, time1; // shutter open/close times
};

