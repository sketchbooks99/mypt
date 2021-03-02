#include <iostream>

#include "../core/MathUtil.h"

using namespace mypt;

struct Hoge {
    int a;
    float b;
    vec3 c;
};

using HogePtr = Hoge*;

struct Fuga {
    void create(const Hoge& hoge_a, Hoge hoge_b = {} ) {
        m_hoge_a = hoge_a;
        
        if (hoge_b) {
            m_hoge_b.a = 1;
            m_hoge_b.b = 2.0f;
            m_hoge_b.c = vec3(3.0f, 4.0f, 5.0f);
        }
    }
private:
    Hoge m_hoge_a;
    Hoge m_hoge_b;
}

int main() {
    
}