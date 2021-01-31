#pragma once

/** Abstract class for several sampling strategies
 * 
 * TODO:
 *  - Basic implementation
 *  - Uniform
 *  - Random
 *  - Jitter
 *  - SOBOL
 * 
 **/

namespace mypt {

class Sampler {
public:
    Sampler(int spp) : samples_per_pixels(spp) {}
    virtual Float sample() const = 0;
private:
    int samples_per_pixels;
};

}