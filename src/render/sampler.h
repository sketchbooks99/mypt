#pragma once

#include "../core/math_util.h"

/** Abstract class for several sampling strategies
 * 
 * TODO:
 *  - [ ] Basic implementation
 *  - [ ] Uniform
 *  - [ ] Random
 *  - [ ] Jitter
 *  - [ ] Sobol
 * 
 **/

namespace mypt {

class Sampler {
public:
    explicit Sampler(int spp) : samples_per_pixels(spp) {}
    virtual Float sample() const = 0;
private:
    int samples_per_pixels;
};

}