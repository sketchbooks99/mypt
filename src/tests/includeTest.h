#include <iostream>

class Hoge {
public:
    Hoge(std::string name) : name(name) {}
    ~Hoge() {}

    void burk();
private:
    std::string name;
};