#include <iostream>

int main(int argc, const char * argv[]) {
    std::string S;
    std::cin >> S;
    int N = (int)S.length();
    int* changes = new int[N + 1];
    unsigned int Q;
    std::cin >> Q;
    for(unsigned int i = 0, L, R; i < Q; ++i) {
        std::cin >> L >> R;
        if (L > R) {
            std::swap(L, R);
        }
        ++changes[L - 1];
        --changes[R];
    }
    bool invert = false;
    for(int i = 0; i < N; ++i) {
        if (abs(changes[i]) % 2 == 1) {
            invert = !invert;
        }
        if (invert) {
            S[i] > 90 ? S[i] -= 32 : S[i] += 32;
        }
    }
    int i = 0;
    do {
        std::cout << S[i];
        i++;
    } while(S[i] != 0);
    delete[] changes;
    return 0;
}
