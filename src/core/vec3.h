#pragma once

#include <iostream>
#include <cmath>

#include "Util.h"

template <typename Type>
class type3 {
public:
    type3() : x(0), y(0), z(0) {}
    type3(Type e0, Type e1, Type e2) : x(e0), y(e1), z(e2) {}
    type3(Type c) : x(c), y(c), z(c) {}

    // Define cast to other type3
    template <typename OtherType>
    operator type3<OtherType>() { return type3<OtherType>(x, y, z); }
    
    type3 operator-() const { return type3(-x, -y, -z); }
    // Type operator[](int i) const { 
    //     return *((Type*)this + i);
    //  or return (&x)[i];
    // }
    // Type& operator[](int i) {
    //     return *((Type*)this + i);
    //  or return (&x)[i];
    // }
    Type operator[](int i) const {
        switch(i) {
        case 0:  return x; break;
        case 1:  return y; break;
        case 2:  return z; break;
        default: throw std::runtime_error("Invalid index number to access vec3 members!\n");
        }
    }
    Type& operator[](int i) {
        switch(i) {
        case 0:  return x; break;
        case 1:  return y; break;
        case 2:  return z; break;
        default: throw std::runtime_error("Invalid index number to access vec3 members!\n");
        }
    }

    bool is_near_zero() const {
        // Return true if the vector is close to zero in all dimensions
        const auto eps = 1e-8;
        return (fabs(x) < eps) && (fabs(y) < eps) && (fabs(z) < eps);
    }

    type3& operator+=(const type3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    type3& operator*=(const Type t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    
    type3 &operator/=(const Type t) {
        return *this *= 1/t;
    }
    
    double length() const {
        return sqrt(length_squared());
    }
    
    Type length_squared() const {
        return x*x + y*y + z*z;
    }

    inline static type3 random() {
        return type3(random_double(), random_double(), random_double());
    }

    inline static type3 random(Type min, Type max) {
        return type3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
    
public:
    Type x, y, z;
};

// vec3 utility functions
template <typename Type>
inline std::ostream& operator<<(std::ostream &out, const type3<Type> &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

template <typename Type>
inline type3<Type> operator+(const type3<Type> &u, const type3<Type> &v) {
    return type3<Type>(u.x + v.x, u.y + v.y, u.z + v.z);
}

template <typename Type>
inline type3<Type> operator-(const type3<Type> &u, const type3<Type> &v) {
    return type3<Type>(u.x - v.x, u.y - v.y, u.z - v.z);
}

template <typename Type>
inline type3<Type> operator*(const type3<Type> &u, const type3<Type> &v) {
    return type3<Type>(u.x * v.x, u.y * v.y, u.z * v.z);
}

template <typename Type>
inline type3<Type> operator*(double t, const type3<Type> &v) {
    return type3<Type>(t*v.x, t*v.y, t*v.z);
}

template <typename Type>
inline type3<Type> operator*(const type3<Type> &v, double t) {
    return t * v;
}

template <typename Type>
inline type3<Type> operator/(type3<Type> v, double t) {
    return (1/t) * v;
}

template <typename Type>
inline double dot(const type3<Type> &u, const type3<Type> &v) {
    return u.x * v.x
    + u.y * v.y
    + u.z * v.z;
}

template <typename Type>
inline type3<Type> cross(const type3<Type> &u, const type3<Type> &v) {
    return type3<Type>(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

using vec3 = type3<double>;
using uint3 = type3<unsigned int>;
using int3 = type3<int>;
using RGB = type3<unsigned char>;

inline vec3 normalize(vec3 v) {
    return v.length() != 0 ? v / v.length() : vec3();
}

inline vec3 random_unit_vector() {
    auto a = random_double(0, 2*pi);
    auto z = random_double(-1,1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

inline vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1,1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline vec3 random_in_unit_disk() {
    while(true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}
