#include "../core/MathUtil.h"
#include "../core/Util.h"

int main() {
    int inside_circle = 0;
    int inside_circle_stratified = 0;
    int sqrt_N = 1000;
    for(int i=0; i<sqrt_N; i++) {
        for(int j=0; j<sqrt_N; j++) {
            auto x = random_Float(-1, 1);
            auto y = random_Float(-1, 1);
            if(x*x + y*y < 1)
                inside_circle++;
            x = 2*((i + random_Float()) / sqrt_N) - 1;
            y = 2*((j + random_Float()) / sqrt_N) - 1;
            if(x*x + y*y < 1)
                inside_circle_stratified++;
        }
    }

    auto N = static_cast<Float>(sqrt_N) * sqrt_N;
    std::cout << std::fixed << std::setprecision(12);
    std::cout 
        << "Regular    Estimate of Pi = "
        << 4*Float(inside_circle) / (sqrt_N*sqrt_N) << "\n"
        << "Stratified Estimate of Pi = "
        << 4*Float(inside_circle_stratified) / (sqrt_N*sqrt_N) << "\n";
}