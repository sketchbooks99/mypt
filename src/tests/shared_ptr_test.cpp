#include "../core/Util.h"

class Hoge {
public:
    Hoge(int a) : a(a) {}
    ~Hoge() {
        std::cout << "Hoge.a: " << a << std::endl;
    }
private:
    int a;
};

int main() {
    int a = 10;
    std::shared_ptr<Hoge> hoge_ptr = std::make_shared<Hoge>(a);
    return 0;
}