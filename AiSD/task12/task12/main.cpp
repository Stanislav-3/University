#include <iostream>

int main(int argc, const char * argv[]) {
    unsigned long int X;
    std::cin >> X;
    int lowRank = X % 10;
    if (lowRank == 0) {
        std::cout << "NO";
    }
    else {
        std::cout << lowRank;
    }
    return 0;
}
