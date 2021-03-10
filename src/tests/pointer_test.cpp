#include <iostream>

struct Hoge {
    Hoge(int a, const std::string& b) : a(a), b(b) {}

    void print_member() { 
        std::cout << "a: " << a << " b: " + b << std::endl;
    }
    int a;
    std::string b;
};

int main() {
    void* ptr = new Hoge(1, "Hoge");
    reinterpret_cast<Hoge*>(ptr)->print_member();

    return 0;
}