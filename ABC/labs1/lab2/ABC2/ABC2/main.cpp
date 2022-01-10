#include <iostream>
#include <string>
#define bits 16
using namespace std;

string Negate(string& bin_num);
string Complement(int number);
string Multiply(const int m, const int r);
string AddBinary(string& lhs, string& rhs);
int SignedMagnitude(string& number);
string reverse(string str);

int main(int argc, const char * argv[]) {
     cout << '-' << pow(2, bits - 1) << " ≤ number ≤ " << pow(2, bits - 1) - 1 << '\n';
     int first, second;
     cout << "Enter the first number: ";
     cin >> first;
     cout << "Enter the second number: ";
     cin >> second;
     try {
         string res = Multiply(first, second);
         std::cout << "Product of " << first << " * " << second << " = "<< SignedMagnitude(res) << '\n';
     }
     catch (overflow_error& e){
         string num = e.what();
         cout << "Overflow: " << SignedMagnitude(num) << '\n';
     }
     catch(exception& e){
         cout <<"Error! " << e.what() << '\n';
     }
     return 0;
}

string Multiply(const int m, const int r) {
    cout << "**********\n";
    cout << "Booth's Algorithm:\n";
    int size = 2 * bits + 2;
    //Initializing string with '0'
    string A, S, P;
    for (int i = 0; i < size; i++) {
        A.append("0");
        S.append("0");
        P.append("0");
    }
    //m to A[high bits] && (-m) to S[high bits] && r to P[low bits]
    string res1 = Complement(m);
    cout << m << " ⟶ " << res1 << '\n';
    string res2 = Complement(-m);
    cout << '-'<< m << " ⟶ " << res2 << '\n';
    string res3 = Complement(r);
    cout << r << " ⟶ " << res3 << '\n';
    for (int i = 0; i < bits; i++) {
        A[i + bits + 1] = res1[i];
        S[i + bits + 1] = res2[i];
        P[i + 1] = res3[i];
    }
    if (A[size - 2] == '1') {
        A[size - 1] = '1';
    }
    else {
        if (m != 0) S[size - 1] = '1';
    }
    cout << "A: " << reverse(A) << '\n';
    cout << "S: " << reverse(S) << '\n';
    cout << "P: " << reverse(P) << '\n';
    //algorithm
    for (int i = 0; i < bits; i++) {
        cout << i + 1 << ") ";
        if (P[0] != P[1]) {
            if (P[0] == '1') {
                //low bits = '10'
                P = AddBinary(P, A);
                cout << "P = P + A = " << reverse(P) << " | ";
            }
            else {
                //low bits = '10'
                P = AddBinary(P, S);
                cout << "P = P + S = " << reverse(P) << " | ";
            }
        }
        cout << "P = P >> 1: " << reverse(P) << " ⟶ ";
        for (int j = 0; j < size - 1; j++) {
            P[j] = P[j + 1];
        }
        if (P[size - 2] == '1') P[size - 1] = '1';
        cout << reverse(P) << '\n';
    }
    cout << "Result: " << reverse(P.substr(1, size - 2)) << '\n';
    cout << "**********\n";
    return P.substr(1, size - 2);;
}

string AddBinary(string& lhs, string& rhs) {
    string result;
    long size = lhs.length();
    for(int i = 0; i < size; ++i) {
        result.append(to_string(lhs[i] + rhs[i] - 2 * '0'));
    }
    for(int i = 0; i < size; ++i){
        if (result[i] > '1') {
            result[i + 1] += (result[i] - '0') / 2;
            result[i] = (result[i] - '0') % 2 + '0';
        }
    }
    if((result[size - 1] != lhs[size - 1]) &&  lhs[size - 1] == rhs[size - 1]) {
        throw std::overflow_error(result);
    }
    return result;
}

string Complement(int number) {
    string in_binary;
    bool neg = false;
    if (number < 0) {
        neg = true;
        number = abs(number);
    }
    while (number) {
        in_binary.append(to_string(number % 2));
        number /= 2;
    }
    if(in_binary.length() < bits) {
        while (in_binary.length() < bits)
            in_binary.append("0");
    }
    if (neg) {
        Negate(in_binary);
    }
    return in_binary;
}

string Negate(string& bin_num) {
    int size = (int)bin_num.length();
    for(int i = 0; i < size; i++) {
        if(bin_num[i] == '0') {
            bin_num[i] = '1';
        }
        else {
            bin_num[i] = '0';
        }
    }
    bin_num[0]++;
    for(int i = 0; i < size; ++i) {
        if (bin_num[i] > '1') {
            bin_num[i + 1] += (bin_num[i] - '0') / 2;
            bin_num[i] = (bin_num[i] - '0') % 2 + '0';
        }
    }
    return bin_num;
}

int SignedMagnitude(string& number) {
    int result = 0;
    int size = (int)number.length();
    bool neg = (number[size - 1] == '1');
    if (neg) {
        for (int i = 0; i < size - 1; i++) {
            if (number[i] == '0') break;
            if (i == bits - 2) return -1 * pow(2, size - 1);
        }
        number = Negate(number);
    }
    for(int i = 0; i < size - 1; ++i) {
        result += (number[i] - '0') * (int)pow(2, i);
    }
    if(neg) {
        result *= -1;
    }
    return result;
}

string reverse(string str)
{
    long n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
    return str;
}
