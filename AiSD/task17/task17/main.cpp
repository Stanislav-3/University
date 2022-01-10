#include <iostream>

int main(int argc, const char * argv[]) {
    unsigned int N;
    std::cin >> N;
    int numDivisor[7] = {1021, 1031, 1033, 1052651, 1054693, 1065023, 1087388483};
    unsigned long int temp;
    bool match[3] = {false, false, false};
    bool found;
    for (int i = 0; i < N; ++i) {
        std::cin >> temp;
        found = false;
        //1divisor
        for (int j = 0; j < 3; ++j) {
            if (temp == numDivisor[j]) {
                match[j] = true;
                found = true;
                break;
            }
        }
        //2divisors
        if (found == false) {
            for (int j = 0; j < 3; ++j) {
                if (temp == numDivisor[3 + j]) {
                    if (j == 0) {
                        match[0] = true;
                        match[1] = true;
                    } else if (j == 1) {
                        match[0] = true;
                        match[2] = true;
                    } else {
                        match[1] = true;
                        match[2] = true;
                    }
                    break;
                }
            }
        }
        //3divisor
        if (temp == numDivisor[6] || (match[0] == true && match[1] == true && match[2] == true)) {
            std::cout << "YES";
            return 0;
        }
    }
    std::cout << "NO";
    return 0;
}
