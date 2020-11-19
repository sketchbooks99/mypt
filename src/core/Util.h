#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <time.h>
#include <iomanip>
#include <assert.h>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double random_double() {
    // Returns a random real in [0, 1)
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min, max).
    return min + (max-min) * random_double();
}

inline int random_int(int min, int max) {
    return static_cast<int> (random_double(min, max+1));
}

inline double clamp(double x, double min, double max) {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

void ASSERT(const bool cond, const std::string& text)
{
    if (!cond)
    {
        throw std::runtime_error(text);
    }
}