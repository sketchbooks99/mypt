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
 * /
class Sampler {
public:
    Sampler(int spp) : samples_per_pixels(spp) {}
    virtual double sample() const = 0;
private:
    int samples_per_pixels;
};