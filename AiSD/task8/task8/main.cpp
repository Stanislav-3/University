#include <iostream>

int main(int argc, const char * argv[]) {
    std::string s;
    std::cin >> s;
    bool ok = false;
    for (int i = 0, j = (int)s.length() - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) {
            std::cout << s.length();
            return 0;
        }
    }
    for (int i = 1; i < (int)s.length(); ++i) {
        if (s[i] != s[0]) {
            ok = true;
            break;
        }
    }
    if (ok) {
        std::cout << s.length() - 1;
    }
    else {
        std::cout << -1;
    }
    return 0;
}
