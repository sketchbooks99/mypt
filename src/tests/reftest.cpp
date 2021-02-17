#include <iostream>
#include "../core/MathUtil.h"

using namespace mypt;

void print_address1(const vec3& a) {
    printf("print_address1: %p\n", &a);
}

void print_address2(vec3 a) {
    printf("print_address2: %p\n", &a);
}

int main(void) {
    vec3 a(1,2,3);
    printf("original: %p\n", &a);
    print_address1(a);
    print_address2(a);

    return 0;
}