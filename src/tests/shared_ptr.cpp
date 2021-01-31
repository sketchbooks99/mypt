#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> a;
    if(a == nullptr) std::cout << "Hoge" << std::endl;
    return 0;
}