#include <iostream>

enum class Type {
    A = 1u << 0,
    B = 1u << 1,
    C = 1u << 2
};

int main(){
    std::cout << static_cast<int>(Type::A) << std::endl;
    std::cout << static_cast<int>(Type::B) << std::endl;
    std::cout << static_cast<int>(Type::C) << std::endl;
}