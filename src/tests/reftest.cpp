#include <iostream>
#include "../core/vec.h"

using namespace mypt;

void print_address1(const vec3& a) {
    printf("print_address1: %p\n", &a);
}

void print_address2(vec3 a) {
    printf("print_address2: %p\n", &a);
}

int switch_func(int val) {
    switch(val) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
        case 3:
            return 3;
        case 4:
            return 4;
        default: 
            return 0;
    }
}

int main(void) {
    vec3 a(1,2,3);
    printf("original: %p\n", &a);
    print_address1(a);
    print_address2(a);

    for (int i=0; i<5; i++) {
        std::cout << switch_func(i) << std::endl;
    }

    return 0;
}