#include <iostream>

struct vec2 {
    vec2() : x(0), y(0) {} 
    vec2(float x, float y) : x(x), y(y) {}
    vec2(float t) : x(t), y(t) {}

    float x, y;
};

struct vec3 {
    vec3() : x(0), y(0), z(0) {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    vec3(float t) : x(t), y(t), z(t) {}

    explicit operator vec2() const { return vec2(x, y); }

    float x, y, z;
};

std::ostream& operator<<(std::ostream& out, const vec2& v) {
    return out << v.x << ' ' << v.y;
}

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

void func(const vec2& v1, const vec3& v2) {
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
}

int main() {
    vec2 v1(1,2);
    vec3 v2(3,4,5);
    func(v1, v2);
    func((vec2)v2, vec3(v1.x, v1.y, 1.0));
    return 0;
}