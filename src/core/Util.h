#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <assert.h>
#include <random>

namespace mypt {
// ----- Mathmatical utility values and functions -----
// Constants
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double random_double() {
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

// ----- Utility functions -----
inline void ASSERT(const bool cond, const std::string& text)
{
    if (!cond) throw std::runtime_error(text);
}

// ref: https://qiita.com/iseki-masaya/items/70b4ee6e0877d12dafa8
inline std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> elements;
    std::string item;

    for(char ch: s)
    {
        if(ch == delimiter) {
            if(!item.empty())
                elements.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if(!item.empty())
        elements.push_back(item);
    return elements;
}
}