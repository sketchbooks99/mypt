#pragma once

#include <iostream>
#include <cmath>

#include "Util.h"

template <typename T>
class type2 {
public:
    type2() : x(0), y(0) {}
    type2(T e0, T e1) : x(e0), y(e1) {}
    type2(T c) : x(c), y(c) {}

    T operator[](int i) const { 
        if(i == 0) return x;
        else if(i == 1) return y;
    }
    T& operator[](int i) {
        if(i == 0) return x;
        else if(i == 1) return y;
    }

    type2 operator-() const { return type2(-x, -y); }

    type2& operator+=(const type2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    type2& operator*=(const T t) {
        x *= t;
        y *= t;
        return *this;
    }

    type2& operator/=(const T t) {
        return *this *= 1/t;
    }

    T length() const {
        return sqrt(length_squared());
    }

    T length_squared() const {
        return x*x + y*y;
    }

    inline static type2 random(){
        return type2(random_double(), random_double());
    }

    inline static type2 random(T min, T max) {
        return type2(random_double(min, max), random_double(min, max));
    }
public:
    T x, y;
};

typedef type2<double> vec2;
typedef type2<unsigned int> uint2;
typedef type2<int> int2;

// Utility functions of type2
template <typename T>
inline std::ostream& operator<<(std::ostream &out, const type2<T> &v) {
    return out << v.x << ' ' << v.y;
}

template <typename T>
inline type2<T> operator+(const type2<T> &u, const type2<T> &v) { return type2<T>(u.x+v.x, u.y+v.y); }

template <typename T>
inline type2<T> operator-(const type2<T> &u, const type2<T> &v) { return type2<T>(u.x-v.x, u.y-v.y); }

template <typename T>
inline type2<T> operator*(const type2<T> &u, const type2<T> &v) { return type2<T>(u.x*v.x, u.y*v.y); }

template <typename T>
inline type2<T> operator*(double t, const type2<T> &v) { return type2<T>(t*v.x, t*v.y); }

template <typename T>
inline type2<T> operator/(const type2<T> &u, double t) { return (1/t) * u; }

template <typename T>
inline T dot(const type2<T> &u, const type2<T> &v) { return u.x*v.x + u.y*v.y; }

template <typename T>
inline type2<T> cross(const type2<T> &u, const type2<T> &v) { return u.x*v.y - u.y*v.x; }

template <typename T>
inline type2<T> unit_vector(type2<T> v) { return v / v.length(); }