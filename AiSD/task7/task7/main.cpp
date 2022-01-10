#include <iostream>

int main(int argc, const char * argv[]) {
    int dX, dY, X1, X2, Y1, Y2;
    std::cin >> dX >> dY >> X1 >> Y1 >> X2 >> Y2;
    dX = abs(X1 - X2);
    dY = abs(Y1 - Y2);
    if (dX == dY) {
        std::cout << "NO";
    } else {
        std::cout << "YES";
    }
    return 0;
}
