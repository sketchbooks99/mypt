#include <iostream>

struct Hoge {
private:
    int a, b;
    float c, d;

public:
    Hoge(int a, int b, float c, float d) : a(a), b(b), c(c), d(d) {}

    Hoge operator*(const Hoge& h) {
        return Hoge(a*h.a, b*h.b, c*h.c, d*h.d); 
    }

    Hoge operator*=(const Hoge& h) {
        a *= h.a; b *= h.b; 
        c *= h.c; d *= h.d;
        return *this;
    }

    bool operator==(const Hoge& h) {
        return (a == h.a) &&
               (b == h.b) && 
               (c == h.c) && 
               (d == h.d);
    }

    friend std::ostream& operator<<(std::ostream& out, const Hoge& h);
};

std::ostream& operator<<(std::ostream& out, const Hoge& h) {
    return out << h.a << ' ' << h.b << ' ' << h.c << ' ' << h.d;
}

int main() {
    Hoge hoge1 = {1,2,3,4};
    Hoge hoge2 = {5,6,7,8};

    auto hoge = hoge1 * hoge2;
    hoge1 *= hoge2;
    std::cout << hoge << ", " << hoge1 << std::endl;

    std::cout << (int)(hoge1 == hoge2) << std::endl;
    std::cout << (int)(hoge1 == hoge1) << std::endl;

    return 0;
}