#include <iostream>
#include <algorithm>

int main(int argc, const char * argv[]) {
    int N;
    std::cin >> N;
    int *A = new int[N];
    for(int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    std::sort(A, A + N);
    if (N == 2) {
        std::cout << (long long int)A[0] * (long long int)A[1];
    }
    else {
        long long int num1 = (long long int)A[0] * (long long int)A[1];
        long long int num2 = (long long int)A[N - 1] * (long long int)A[N - 2];
        if (num1 > num2) {
            std::cout << num1;
        }
        else {
            std::cout << num2;
        }
    }
    delete [] A;
    return 0;
}
