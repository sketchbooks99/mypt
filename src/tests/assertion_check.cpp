#include "../core/Util.h"

using namespace mypt;

void verify_value(int a) {
    ASSERT(a == 1 || a == 3, "[a: " + std::to_string(a) + "], a has invalid value.");
    std::cout << a << std::endl;
    return;
}

int main() {
    for(int i=1; i<4; i++) 
        verify_value(i);
    return  0;
}