#include <iostream>
#include <tuple>
#include <string>
#include <vector>

struct Base {
    virtual void print_member() const = 0;
};

struct Hoge : public Base {
    Hoge(char a, int b, const std::string& str)
    : a(a), b(b), str(str) {}
    char a;
    int b;
    std::string str;

    void print_member() const override {
        std::cout << (int)a << ' ' << b << ' ' << str << std::endl;
    }
};

struct Fuga : public Base {
    Fuga(char a, int b, float c, double d, const std::string& str)
    : a(a), b(b), c(c), d(d), str(str) {}
    char a;
    int b;
    float c;
    double d;
    std::string str;

    void print_member() const override {
        std::cout << (int)a << ' ' << b << ' ' << c << ' ' << d << ' ' << str << std::endl;
    }
};

template <typename T, typename... Args>
void construct(T** ptr, Args... args) {
    (*ptr) = new T(args...);
}

void construct_hoge(Base** ptr, char a, int b, const std::string& str)
{
    (*ptr) = new Hoge(a, b, str);
}


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

    // Basic pointer
    std::vector<Base*> bases(10);
    for(size_t i=0; i<bases.size(); i++) {
        bases[i] = (Base*)malloc(sizeof(Base*));
        if (i%2 == 0)
            construct((Hoge**)&bases[i], (char)i*2, i*2+1, "hoge"+std::to_string(i));
        else 
            construct((Fuga**)&bases[i], (char)i*2, i*2+1, (float)(i*2+2), (double)(i*2+3), "fuga"+std::to_string(i));
    }
    for(auto& b : bases) b->print_member();
}

