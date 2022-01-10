#include <iostream>

int main(int argc, const char * argv[]) {
    unsigned int N, i = 0;
    unsigned long int APrev, Ai, AMax, steps = 0;
    std::cin >> N >> Ai;
    AMax = Ai;
    do {
        APrev = Ai;
        std::cin >> Ai;
        if (AMax < Ai) {
            steps += Ai - AMax;
            AMax = Ai;
        } else {
            APrev > Ai ? (steps += APrev - Ai):0;
        }
        ++i;
    } while(i < N - 1);
    std::cout << steps;
    return 0;
}
