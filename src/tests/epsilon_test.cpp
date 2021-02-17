#include <iostream>

#if 1
using Float = double; 
#else
using Float = float;
#endif

int main() {
    Float a = std::numeric_limits<Float>::infinity();
    std::cout << (Float)(a-1.f) << std::endl;
}