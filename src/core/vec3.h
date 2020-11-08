#pragma once

#include <iostream>
#include <cmath>

#include "Util.h"

template <typename T>
class type3 {
public:
    type3() : x(0), y(0), z(0) {}
    type3(T e0, T e1, T e2) : x(e0), y(e1), z(e2) {}
    type3(T c) : x(c), y(c), z(c) {}
    
    type3 operator-() const { return type3(-x, -y, -z); }
    double operator[](int i) const { 
        if(i == 0) return x;
        else if(i == 1) return y;
        else if(i == 2) return z;
    }
    double& operator[](int i) {
        if(i == 0) return x;
        else if(i == 1) return y;
        else if(i == 2) return z;
    }
    
    type3& operator+=(const type3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    type3& operator*=(const T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    
    type3 &operator/=(const T t) {
        return *this *= 1/t;
    }
    
    double length() const {
        return sqrt(length_squared());
    }
    
    double length_squared() const {
        return x*x + y*y + z*z;
    }

    inline static type3 random() {
        return type3(random_double(), random_double(), random_double());
    }

    inline static type3 random(T min, T max) {
        return type3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
    
public:
    T x, y, z;
};

// vec3 utility functions
template <typename T>
inline std::ostream& operator<<(std::ostream &out, const type3<T> &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

template <typename T>
inline type3<T> operator+(const type3<T> &u, const type3<T> &v) {
    return type3<T>(u.x + v.x, u.y + v.y, u.z + v.z);
}

template <typename T>
inline type3<T> operator-(const type3<T> &u, const type3<T> &v) {
    return type3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

template <typename T>
inline type3<T> operator*(const type3<T> &u, const type3<T> &v) {
    return type3<T>(u.x * v.x, u.y * v.y, u.z * v.z);
}

template <typename T>
inline type3<T> operator*(double t, const type3<T> &v) {
    return type3<T>(t*v.x, t*v.y, t*v.z);
}

template <typename T>
inline type3<T> operator*(const type3<T> &v, double t) {
    return t * v;
}

template <typename T>
inline type3<T> operator/(type3<T> v, double t) {
    return (1/t) * v;
}

template <typename T>
inline double dot(const type3<T> &u, const type3<T> &v) {
    return u.x * v.x
    + u.y * v.y
    + u.z * v.z;
}

template <typename T>
inline type3<T> cross(const type3<T> &u, const type3<T> &v) {
    return type3<T>(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

typedef type3<double> vec3;
typedef type3<unsigned int> uint3;
typedef type3<int> int3;
typedef type3<unsigned char> RGB;

// TODO: Implement of zero-division check. If v = vec3(0.0), zero-division will occur.
inline vec3 normalize(vec3 v) {
    return v / v.length();
}

vec3 random_unit_vector() {
    auto a = random_double(0, 2*pi);
    auto z = random_double(-1,1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1,1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else 
        return -in_unit_sphere;
}

vec3 random_in_unit_disk() {
    while(true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}
