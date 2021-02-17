#pragma once

#include <iostream>
#include <cmath>

#include "Util.h"

namespace mypt {

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
    Type operator[](int i) const {
        ASSERT(i < 3, "Invalid index number to access vec3 members!\n");
        return (&x)[i];
    }
    Type& operator[](int i) {
        ASSERT(i < 3, "Invalid index number to access vec3 members!\n");
        return (&x)[i];
    }

    bool is_near_zero() const {
        // Return true if the vector is close to zero in all dimensions
        return (fabs(x) < eps) && (fabs(y) < eps) && (fabs(z) < eps);
    }

    type3& operator+=(const type3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    type3& operator-=(const type3 &v) {
        return *this += (-v);
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
    
    Float length() const {
        return sqrt(length_squared());
    }
    
    Type length_squared() const {
        return x*x + y*y + z*z;
    }

    inline static type3 random() {
        return type3(random_float(), random_float(), random_float());
    }

    inline static type3 random(Type min, Type max) {
        return type3(random_float(min, max), random_float(min, max), random_float(min, max));
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
inline bool operator==(const type3<Type> &u, const type3<Type> &v) {
    if(u.x == v.x && u.y == v.y && u.z == v.z) return true;
    else return false;
}

template <typename Type>
inline bool operator!=(const type3<Type> &u, const type3<Type> &v) {
    if(u.x != v.x || u.y != v.y || u.z != v.z) return true;
    else return false;
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
inline type3<Type> operator*(Float t, const type3<Type> &v) {
    return type3<Type>(t*v.x, t*v.y, t*v.z);
}

template <typename Type>
inline type3<Type> operator*(const type3<Type> &v, Float t) {
    return t * v;
}

template <typename Type>
inline type3<Type> operator/(type3<Type> v, Float t) {
    return (1.f/t) * v;
}

template <typename Type>
inline Float dot(const type3<Type> &u, const type3<Type> &v) {
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

using vec3 = type3<Float>;
using uint3 = type3<unsigned int>;
using int3 = type3<int>;
using RGB = type3<unsigned char>;

inline vec3 normalize(vec3 v) {
    return v.length() != 0 ? v / v.length() : vec3();
}

inline vec3 random_unit_vector() {
    auto a = random_float(0, 2*pi);
    auto z = random_float(-1,1);
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

inline vec3 random_to_sphere(Float radius, Float distance_squared) {
    auto r1 = random_float();
    auto r2 = random_float();
    auto z = 1 + r2*(sqrt(1-radius*radius/distance_squared) - 1);

    auto phi = 2*pi*r1;
    auto x = cos(phi)*sqrt(1-z*z);
    auto y = sin(phi)*sqrt(1-z*z);

    return vec3(x, y, z);
}

inline vec3 random_in_unit_disk() {
    while(true) {
        auto p = vec3(random_float(-1, 1), random_float(-1, 1), 0);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_cosine_direction() {
    auto r1 = random_float();
    auto r2 = random_float();
    auto z = sqrt(1-r2);

    auto phi = 2*pi*r1;
    auto x = cos(phi)*sqrt(r2);
    auto y = sin(phi)*sqrt(r2);
    return vec3(x, y, z);
}

inline RGB vec2color(const vec3& c, float scale) {
    // auto r = sqrt(scale * c.x);
    // auto g = sqrt(scale * c.y);
    // auto b = sqrt(scale * c.z);
    auto r = scale * c.x;
    auto g = scale * c.y;
    auto b = scale * c.z;
    RGB rgb_color(static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999)),
                    static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999)),
                    static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999)));
    return rgb_color;
}

}
