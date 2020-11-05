//
//  vec4.h
//  RayTracing
//
//  Created by 木内舜司 on 2020/04/11.
//  Copyright © 2020 木内舜司. All rights reserved.
//

#ifndef VEC4_H
#define VEC4_H

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
    }
    T& operator[](int i) {
        if(i == 0) return x;
        else if(i == 1) return y;
        else if(i == 2) return z;
    }
    
    type4& operator+=(const type4 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    type4& operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    
    type4 &operator/=(const double t) {
        return *this *= 1/t;
    }
    
    double length() const {
        return sqrt(length_squared());
    }
    
    double length_squared() const {
        return x*x + y*y + z*z;
    }

    inline static type4 random() {
        return type4(random_double(), random_double(), random_double());
    }

    inline static type4 random(T min, T max) {
        return type4(random_double(min, max), random_double(min, max), random_double(min, max));
    }
    
    /*void write_color(std::ostream &out, int samples_per_pixel) {
        // Devide the color total by the number of samples.
        // for a gamma value of 2.0
        auto scale = 1.0 / samples_per_pixel;
        auto r = sqrt(scale * x);
        auto g = sqrt(scale * y);
        auto b = sqrt(scale * z);

        // Write the translated [0, 255] value of each color component.
        out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    }*/
    
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
inline vec4 unit_vector(vec4 v) {
    return v / v.length();
}

#endif /* vec3_h */
