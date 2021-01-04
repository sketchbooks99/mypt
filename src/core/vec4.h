#pragma once

#include <iostream>
#include <cmath>

#include "Util.h"
#include "vec3.h"

namespace mypt {

template <typename Type>
class type4 {
public:
    type4() : x(0), y(0), z(0), w(0) {}
    type4(Type e0, Type e1, Type e2, Type e3) : x(e0), y(e1), z(e2), w(e3) {}
    type4(Type c) : x(c), y(c), z(c), w(c) {}
    type4(type3<Type> v, Type w) : x(v.x), y(v.y), z(v.z), w(w) {}

    template <typename OtherType>
    operator type4<OtherType>() { return type4<OtherType>(x, y, z, w); }
    
    type4 operator-() const { return type4(-x, -y, -z); }
    Type operator[](int i) const { 
        ASSERT(i < 4, "Invalid index number to access vec3 members!\n");
        return (&x)[i];
    }
    Type& operator[](int i) {
        ASSERT(i < 4, "Invalid index number to access vec3 members!\n");
        return (&x)[i];
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

    inline static type4 random(Type min, Type max) {
        return type4(random_double(min, max), 
                     random_double(min, max), 
                     random_double(min, max),
                     random_double(min, max));
    }
    
public:
    Type x, y, z, w;
};

// vec4 utility functions
template <typename Type>
inline std::ostream& operator<<(std::ostream &out, const type4<Type> &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
}

template <typename Type>
inline type4<Type> operator+(const type4<Type> &u, const type4<Type> &v) {
    return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

template <typename Type>
inline type4<Type> operator-(const type4<Type> &u, const type4<Type> &v) {
    return type4<Type>(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

template <typename Type>
inline type4<Type> operator*(const type4<Type> &u, const type4<Type> &v) {
    return type4<Type>(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

template <typename Type>
inline type4<Type> operator*(double t, const type4<Type> &v) {
    return type4<Type>(t*v.x, t*v.y, t*v.z, t*v.w);
}

template <typename Type>
inline type4<Type> operator*(const type4<Type> &v, double t) {
    return t * v;
}

template <typename Type>
inline type4<Type> operator/(type4<Type> v, double t) {
    return (1/t) * v;
}

template <typename Type>
inline double dot(const type4<Type> &u, const type4<Type> &v) {
    return u.x * v.x
    + u.y * v.y
    + u.z * v.z;
}

template <typename Type>
inline type4<Type> cross(const type4<Type> &u, const type4<Type> &v) {
    return type4<Type>(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x, 
                1.0f);
}

using vec4 = type4<double>;
using uint4 = type4<unsigned int>;
using int4 = type4<int>;
using RGBA = type4<unsigned char>;

// TODO: Implement of zero-division check. If v = vec4(0.0), zero-division will occur.
inline vec4 normalize(vec4 v) {
    return v / v.length();
}

}