#pragma once

#include "util.h"

namespace mypt {

using GRAY = unsigned char;

// ----- Mathmatical utility values and functions -----
// Constants
constexpr Float infinity = std::numeric_limits<Float>::infinity();
constexpr Float pi = 3.1415926535897932385;
constexpr Float eps = 1e-10f;

// Functions
inline Float degrees_to_radians(Float degrees) {
    return degrees * pi / 180;
}

inline Float ffmin(Float a, Float b) { return a <= b ? a : b; }
inline Float ffmax(Float a, Float b) { return a >= b ? a : b; }

inline Float random_float() {
    return rand() / (RAND_MAX + 1.0);
}

inline Float random_float(Float min, Float max) {
    // Returns a random real in [min, max).
    return min + (max-min) * random_float();
}

inline int random_int(int min, int max) {
    return static_cast<int> (random_float(min, max+1));
}

inline Float clamp(Float x, Float min, Float max) {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

template <typename T>
inline T lerp(T a, T b, Float t) {
    t = clamp(0, 1, t);
    return t * a + (1-t) * b;
}

}