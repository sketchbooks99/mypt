#include <iostream>
#include <typeinfo>

#if 0
using Float = double;
#else 
using Float = float;
#endif

int main() {
    Float a = 1.f;
    std::cout << typeid(Float).name() << std::endl;
    return 0;
}