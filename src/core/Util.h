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
#include <map>

// #ifdef defined(__linux__) || defined(__APPLE__)
//     #define __posix__
//     #include <execinfo.h>
// #elif defined(__MINGW32__)
//     #include <windows.h>
// #endif

namespace mypt {

// ----- Mathmatical utility values and functions -----
// Constants
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;
constexpr double eps = 1e-10f;

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

// Get backtrace informations
// ref: https://qiita.com/nanashi/items/19e2c9558be00d310eaa
// inline std::string get_backtrace_info() {
//     std::string result;
// #if defined(__posix__)
//     const static ssize_t trace_frames_max = 100;
//     void* trace_frames[trace_frames_max] = {};
//     int size = ::backtrace(trace_frames, trace_frames_max);
//     if(size < 0 || size >= trace_frames_max) 
//         return std::string("get_backtrace_info error: backtrace failed");
//     char** trace_symbols = ::backtrace_symbols(trace_frames, trace_frames_max);
//     if(!trace_symbols)
//         return std::string("get_backtrace_info error: get symbol failed");
//     for(ssize_t i=1; i<size; i++) {
//         result.append(trace_symbols[i]);
//         result.append("\n");
//     }
//     free(trace_symbols);
//     trace_symbols = nullptr;
// #elif defined(__MINGW32__)
//     const static ssize_t = trace_frames_max = 50;
//     void* trace_frames[trace_frames_max] = {};
//     int size = ::CaptureStackBackTrace(0, trace_frames_max, trace_frames, nullptr);
//     if(size < 0 || size >= trace_frames_max)
//         return std::string("get_backtrace_info error: backtrace failed");
//     std::ostringstream address_str;
//     for(ssize_t i=1; i<size; i++) {
//         int64_t address = reinterpret_cast<int64_t>(trace_frames[i]);
//         address_str << i << ": 0x" << std::hex << address << "\n";
//     }
//     result.assign(address_str.str());
// #else 
//     return std::string("get_backtrace_info error: unknown platform");
// #endif 
//     return result;
// }

}