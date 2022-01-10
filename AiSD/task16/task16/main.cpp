#include <iostream>
#include <algorithm>

int main(int argc, const char * argv[]) {
    std::string X;
    std::cin >> X;
    bool ok = false;
    int index = 0;
    
    for (int i = (int)X.size() - 2; i >= 0; --i) {
        for (int j = (int)X.size(); j > i; --j) {
            if (X[i] < X[j]) {
                std::swap(X[i], X[j]);
                ok = true;
                index = i + 1;
                goto label;
            }
        }
    }
    
    label:
    if (ok) {
        std::sort(X.begin() + index, X.end());
        std::cout << X;
    }
    else {
        std::cout << -1;
    }
    return 0;
}
