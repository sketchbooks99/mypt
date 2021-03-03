#include "../core/Util.h"

using namespace mypt;

enum class Hoge {
    A,
    B,
    C,
    D
};

std::ostream& operator<<(std::ostream& out, Hoge hoge) {
    switch(hoge) {
    case Hoge::A: return out << "A";
    case Hoge::B: return out << "B";
    case Hoge::C: return out << "C";
    case Hoge::D: return out << "D";
    default:      return out << "";
    }
}

template <typename T>
std::string to_str(T t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

void func(Hoge hoge) {
    Assert(hoge == Hoge::A || hoge == Hoge::B, "This Hoge " + to_str(hoge) + " is not supported type!");

    std::cout << to_str(hoge) << std::endl;
}

int main() {
    func(Hoge::A);
    func(Hoge::B);
    func(Hoge::C);
    return 0;
}