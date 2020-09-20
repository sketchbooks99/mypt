#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>

#include "Util.h"

class vec2 {
public:
    vec2() : x(0), y(0) {}
    vec2(double e0, double e1) : x(e0), y(e1) {}
    vec2(double c) : x(c), y(c) {}

    double operator[](int i) const { 
        if(i == 0) return x;
        else if(i == 1) return y;
    }
    double& operator[](int i) {
        if(i == 0) return x;
        else if(i == 1) return y;
    }

    vec2 operator-() const { return vec2(-x, -y); }

    vec2& operator+=(const vec2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    vec2& operator*=(const double t) {
        x *= t;
        y *= t;
        return *this;
    }

    vec2& operator/=(const double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return x*x + y*y;
    }

    inline static vec2 random(){
        return vec2(random_double(), random_double());
    }

    inline static vec2 random(double min, double max) {
        return vec2(random_double(min, max), random_double(min, max));
    }
public:
    double x, y;
};

// Utility functions of vec2
inline std::ostream& operator<<(std::ostream &out, const vec2 &v) {
    return out << v.x << ' ' << v.y;
}

inline vec2 operator+(const vec2 &u, const vec2 &v) { return vec2(u.x+v.x, u.y+v.y); }

inline vec2 operator-(const vec2 &u, const vec2 &v) { return vec2(u.x-v.x, u.y-v.y); }

inline vec2 operator*(const vec2 &u, const vec2 &v) { return vec2(u.x*v.x, u.y*v.y); }

inline vec2 operator*(double t, const vec2 &v) { return vec2(t*v.x, t*v.y); }

inline vec2 operator/(const vec2 &u, double t) { return (1/t) * u; }

inline double dot(const vec2 &u, const vec2 &v) { return u.x*v.x + u.y*v.y; }

inline vec2 cross(const vec2 &u, const vec2 &v) { return u.x*v.y - u.y*v.x; }

inline vec2 unit_vector(vec2 v) { return v / v.length(); }

#endif