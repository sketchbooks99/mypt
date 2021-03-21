#include <iostream>

struct Hoge {
    Hoge(int a, const std::string& b) : a(a), b(b) {}

    void print_member() { 
        std::cout << "a: " << a << " b: " + b << std::endl;
    }
    int a;
    std::string b;
};

void rewrite(Hoge& h, const int val, const std::string& str) {
    h.a = val;
    h.b = str;
}

int main() {
    Hoge* hoge = new Hoge(1, "Hoge");
    hoge->print_member();

    rewrite(*hoge, 5, "rewrite");
    hoge->print_member();

    return 0;
}