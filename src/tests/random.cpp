#include <random>
#include <iostream>

#define RND1 0

float random_float1(unsigned int seed) {
    std::mt19937 rnd_src(seed);
    std::uniform_real_distribution<float> rnd_dist(0, 1);
    return rnd_dist(rnd_src);
}

float random_float2(unsigned int seed) {
    return (float)seed;
}

using FuncPtr = float (*) (unsigned int);

#if RND1
FuncPtr Random = random_float1;
#else 
FuncPtr Random = random_float2;
#endif

int main() {
    for(int i=0; i<100; i++)
        std::cout << Random(i) << std::endl;
    
    return 0;
}