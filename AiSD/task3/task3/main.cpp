#include <iostream>
#include <algorithm>
int main(int argc, const char * argv[]) {
    unsigned int N, K;
    long long mod = 1000000007;
    long long A[100000], ans = 1;
    std::cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    std::sort(A, A + N);

    // Ai >= 0
    if (A[0] >= 0) {
        if (A[N - K] == 0) {
            ans = 0;
        } else {
            for (int i = N - K; i < N; ++i) {
                ans *= (A[i] % mod);
                ans %= mod;
            }
        }
        ans < 0 ? (std::cout << mod + ans) : (std::cout << ans);
        return 0;
    }
    //  Ai <= 0
    else if (A[N - 1] <= 0) {
        if (K % 2 == 0) {
            for (int i = 0; i < K; ++i) {
                ans *= (A[i] % mod);
                ans %= mod;
            }
        } else {
            for (int i = N - K; i < N; ++i) {
                ans *= (A[i] % mod);
                ans %= mod;
            }
        }
        ans < 0 ? (std::cout << mod + ans) : (std::cout << ans);
        return 0;
    }
    // A[] has negative and positive values
    else {
        int i = 0, j = N - 1;
        if (K % 2 == 1) {
            ans *= (A[j] % mod);
            ans %= mod;
            --j;
        }
        for (int c = 0; c < K / 2; ++c) {
            if ((A[i]) * (A[i + 1])
                >= (A[j]) * (A[j - 1])) {
                ans *= (A[i] % mod);
                ans %= mod;
                ans *= (A[i + 1] % mod);
                ans %= mod;
                i += 2;
            } else {
                ans *= (A[j] % mod);
                ans %= mod;
                ans *= (A[j - 1] % mod);
                ans %= mod;
                j -= 2;
            }
        }
        ans < 0 ? (std::cout << mod + ans) : (std::cout << ans);
        return 0;
    }
}
