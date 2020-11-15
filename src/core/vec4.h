#pragma once

#include <iostream>
#include <cmath>

#include "Util.h"

template <typename T>
class type4 {
public:
    type4() : x(0), y(0), z(0), w(0) {}
    type4(T e0, T e1, T e2, T e3) : x(e0), y(e1), z(e2), w(e3) {}
    type4(T c) : x(c), y(c), z(c), w(c) {}
    
    type4 operator-() const { return type4(-x, -y, -z); }
    T operator[](int i) const { 
        if(i == 0) return x;
        else if(i == 1) return y;
        else if(i == 2) return z;
        else if(i == 3) return w;
    }
    T& operator[](int i) {
        if(i == 0) return x;
        else if(i == 1) return y;
        else if(i == 2) return z;
        else if(i == 3) return w;
    }
    
    type4& operator+=(const type4 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }
    
    type4& operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        w *= t;
        return *this;
    }
    
    type4 &operator/=(const double t) {
        return *this *= 1/t;
    }
    
    double length() const {
        return sqrt(length_squared());
    }
    
    double length_squared() const {
        return x*x + y*y + z*z + w*w;
    }

    inline static type4 random() {
        return type4(random_double(), random_double(), random_double(), random_double());
    }

    inline static type4 random(T min, T max) {
        return type4(random_double(min, max), 
                     random_double(min, max), 
                     random_double(min, max),
                     random_double(min, max));
    }
    
public:
    T x, y, z, w;
};

// vec4 utility functions
template <typename T>
inline std::ostream& operator<<(std::ostream &out, const type4<T> &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
}

template <typename T>
inline type4<T> operator+(const type4<T> &u, const type4<T> &v) {
    return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

template <typename T>
inline type4<T> operator-(const type4<T> &u, const type4<T> &v) {
    return type4<T>(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

template <typename T>
inline type4<T> operator*(const type4<T> &u, const type4<T> &v) {
    return type4<T>(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

template <typename T>
inline type4<T> operator*(double t, const type4<T> &v) {
    return type4<T>(t*v.x, t*v.y, t*v.z, t*v.w);
}

template <typename T>
inline type4<T> operator*(const type4<T> &v, double t) {
    return t * v;
}

template <typename T>
inline type4<T> operator/(type4<T> v, double t) {
    return (1/t) * v;
}

template <typename T>
inline double dot(const type4<T> &u, const type4<T> &v) {
    return u.x * v.x
    + u.y * v.y
    + u.z * v.z;
}

template <typename T>
inline type4<T> cross(const type4<T> &u, const type4<T> &v) {
    return type4<T>(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x, 
                1.0f);
}

typedef type4<double> vec4;
typedef type4<unsigned int> uint4;
typedef type4<int> int4;
typedef type4<unsigned char> RGBA;

// TODO: Implement of zero-division check. If v = vec4(0.0), zero-division will occur.
inline vec4 normalize(vec4 v) {
    return v / v.length();
}
