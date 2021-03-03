#include <iostream>

void f(const char* str) {
    std::cout << str << std::endl;
}

int main() {
    // const char* str1 = nullptr;     // OK
    // f(str1);
    // std::string str2 = nullptr;     // NG: Runtime error will be called
    const char* str2 = "Hello World!";
    f(str2);

    std::string str3 = "Hello World! (std::string)";
    f(str3.c_str());

    return 0;
}