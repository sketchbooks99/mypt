#include "../core/math_util.h"

using namespace mypt;

int main() {
    for (int i=-5; i<=5; i++) {
        auto val = (float)i + random_float();
        Message("before:", val, "floored:", floorf(val));
    }
    return 0;
}