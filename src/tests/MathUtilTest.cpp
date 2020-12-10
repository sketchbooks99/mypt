#include "../core/MathUtil.h"

struct ONB {
    ONB() {}
    vec3 operator[](int i) { return (&u)[i]; }
    void build_from_w(const vec3& n) {
        w = normalize(n);
        vec3 a = (fabs(w.x) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
        v = normalize(cross(w, a));
        u = cross(w, v); 
    }
public:
    vec3 u, v, w;
};

void cast_test() {
    // Cast test 

    int2 i_v2(127, 255);
    auto f_v2 = static_cast<vec2>(i_v2);
    std::cout << "----- vec2 -----" << std::endl;
    std::cout << "i_v2: " << i_v2 / 10 << std::endl;
    std::cout << "f_v2: " << f_v2 / 10 << std::endl;

    RGB rgb(127, 255, 100);
    auto f_v3 = static_cast<vec3>(rgb);
    std::cout << "----- vec3 -----" << std::endl;
    std::cout << "rgb: " << static_cast<int3>(rgb / 10) << std::endl;
    std::cout << "f_v3: " << f_v3 / 10 << std::endl;

    RGBA rgba(127, 255, 100, 255);
    auto f_v4 = static_cast<vec4>(rgba);
    std::cout << "----- vec4 -----" << std::endl;
    std::cout << "rgba: " << static_cast<int4>(rgba / 10) << std::endl;
    std::cout << "f_v4: " << f_v4 / 10 << std::endl;
}

void ONB_test(){
    ONB onb;
    onb.build_from_w(vec3(0,1,0));
    for(int i=0; i<3; i++)
        std::cout << onb[i] << std::endl;
}

int main() {
    cast_test();
    std::cout << "ONB test" << std::endl;
    ONB_test();
    return 0;
}