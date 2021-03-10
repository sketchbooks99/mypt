#include <iostream>
#include <tuple>
#include <string>

template <typename T, typename... Args>
void construct(T** ptr, Args... args) {
    (*ptr) = new T(args...);
}

struct Hoge {
    Hoge(char a, int b, const std::string& str)
    : a(a), b(b), str(str) {}
    char a;
    int b;
    std::string str;
};

struct Fuga {
    Fuga(char a, int b, float c, double d, const std::string& str)
    : a(a), b(b), c(c), d(d), str(str) {}
    char a;
    int b;
    float c;
    double d;
    std::string str;
};

std::ostream& operator<<(std::ostream& out, const Hoge& hoge) {
    return out << (int)hoge.a << ' ' << hoge.b << ' ' << hoge.str << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Fuga& fuga) {
    return out << (int)fuga.a << ' ' << fuga.b << ' ' << fuga.c << ' ' << fuga.d << ' ' << fuga.str << std::endl;
}

int main() {
    Hoge* hoge = new Hoge(1,2,"hoge1");
    std::cout << *hoge << std::endl;
    construct(&hoge, 3, 4, "hoge2");
    std::cout << *hoge << std::endl;
}

