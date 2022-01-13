#include "util.h"

struct Member1 {
    int a;
    const char* name;
    float b;
};

struct Member2 {
    int a;
    const char* name; 
    float b;
};

std::ostream& operator<<(std::ostream& out, const Member1 m1) {
    out << m1.a << std::endl;
    out << m1.name << std::endl;
    return out << m1.b;
}

class Hoge {
public:
    explicit Hoge(const std::string& name) {
        _init_m1();
        m1.name = name.c_str();
        _init_m2();
        m2.name = name.c_str();
    }

    void print_m1() {
        Message("Hoge.m1:", m1.a, m1.name, m1.b);
    }

    void print_m2() {
        Message("Hoge.m2:", m2.a, m2.name, m2.b);
    }
private:
    void _init_m1() {
        m1.a = 0;
        m1.name = "";
        m1.b = 0.f;
    }
    void _init_m2() {
        m2.a = 1;
        m2.name = "";
        m2.b = 1.f;
    }
    Member1 m1 {};
    Member2 m2 {};
};

int main() {
    Hoge h("dkeokoekdoe");
    h.print_m1();
    h.print_m2();

    Member1 m1 { 1, "member1", 1.0f };
    std::cout << m1 << std::endl;
    return 0;
}