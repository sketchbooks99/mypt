#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

std::string ch_str(const std::string& str) { 
    std::string temp = "__closesthit__" + str;
    return temp;
}

class Type {
public:
    Type(int a, int b) : a(a), b(b) {}
    std::string to_string() {
        std::ostringstream oss;
        oss << "Type {" << std::endl;
        oss << " A : " << a << "," << std::endl;
        oss << " B : " << b << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }
private:
    int a, b;
};

int main() {
    Type type(3,5);
    std::cout << type.to_string() << std::endl;

    std::cout << ch_str("hoge").c_str() << std::endl;

    return 0;
}