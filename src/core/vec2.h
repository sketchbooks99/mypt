#pragma once

#include <iostream>
#include <cmath>

#include "Util.h"

namespace mypt{

template <typename Type>
class type2 {
public:
    type2() : x(0), y(0) {}
    type2(Type e0, Type e1) : x(e0), y(e1) {}
    type2(Type c) : x(c), y(c) {}

    template <typename OtherType>
    operator type2<OtherType>() { return type2<OtherType>(x, y); }

    Type operator[](int i) const { 
        ASSERT(i < 2, "Invalid index number to access vec3 members!\n");
        return (&x)[i];
    }
    Type& operator[](int i) {
        ASSERT(i < 2, "Invalid index number to access vec3 members!\n");
        return (&x)[i];
    }

    type2 operator-() const { return type2(-x, -y); }

    type2& operator+=(const type2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    type2& operator*=(const Type& t) {
        x *= t;
        y *= t;
        return *this;
    }

    type2& operator/=(const Type& t) {
        return *this *= 1/t;
    }

    Type length() const {
        return sqrt(length_squared());
    }

    Type length_squared() const {
        return x*x + y*y;
    }

    inline static type2 random(){
        return type2(random_float(), random_float());
    }

    inline static type2 random(const Type& min, const Type& max) {
        return type2(random_float(min, max), random_float(min, max));
    }
public:
    Type x, y;
};

using vec2 = type2<Float>;
using uint2 = type2<unsigned int>;
using int2 = type2<int>;

// Utility functions of type2
template <typename Type>
inline std::ostream& operator<<(std::ostream &out, const type2<Type> &v) {
    return out << v.x << ' ' << v.y;
}

template <typename Type>
inline type2<Type> operator+(const type2<Type> &u, const type2<Type> &v) { return type2<Type>(u.x+v.x, u.y+v.y); }

template <typename Type>
inline type2<Type> operator-(const type2<Type> &u, const type2<Type> &v) { return type2<Type>(u.x-v.x, u.y-v.y); }

template <typename Type>
inline type2<Type> operator*(const type2<Type> &u, const type2<Type> &v) { return type2<Type>(u.x*v.x, u.y*v.y); }

template <typename Type>
inline type2<Type> operator*(Float t, const type2<Type> &v) { return type2<Type>(t*v.x, t*v.y); }

template <typename Type>
inline type2<Type> operator/(const type2<Type> &u, Float t) { return (1/t) * u; }

template <typename Type>
inline Type dot(const type2<Type> &u, const type2<Type> &v) { return u.x*v.x + u.y*v.y; }

template <typename Type>
inline type2<Type> cross(const type2<Type> &u, const type2<Type> &v) { return u.x*v.y - u.y*v.x; }

template <typename Type>
inline type2<Type> unit_vector(type2<Type> v) { return v / v.length(); }

}