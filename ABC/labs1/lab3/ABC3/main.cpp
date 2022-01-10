#include <iostream>
#include <string>
#define bits 16
using namespace std;

string Negate(string& bin_num);
string Complement(int number);
pair<string, string> Divide(const int dividend, const int divisor);
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
         if (second == 0) {
             throw "Division by 0 is prohibited!!!";
         }
         pair<string, string> res = Divide(first, second);
         int quotient, remainder;
         quotient = SignedMagnitude(res.first);
         if(SignedMagnitude(res.second) < 0) {
             res.second = Negate(res.second);
         }
         remainder = SignedMagnitude(res.second);
         std::cout << "Quotient of " << first << " / " << second << " = "<< quotient << "| Remainder: " << remainder <<'\n';
     }
     catch(char const* e){
         cout <<"Error! " << e << '\n';
     }
     return 0;
}

pair<string, string> Divide(const int dividend, const int divisor) {
    cout << "**********\n";
    //Initializing strings with '0'
    string A, Q, M;
    for (int i = 0; i < bits; i++) {
        A.append("0");
        Q.append("0");
        M.append("0");
    }
    //Initializing strings
    string res1 = Complement(dividend);
    cout << dividend << " ⟶ " << reverse(res1) << '\n';
    string res2 = Complement(divisor);
    cout << divisor << " ⟶ " << reverse(res2) << '\n';
    bool neg = false;
    res1[bits - 1] == '1' ? neg = true : neg = false;
    for (int i = 0; i < bits; i++) {
        A[i] = (int)neg + '0';
        Q[i] = res1[i];
        M[i] = res2[i];
    }
    cout << "A: " << A << '\n';
    cout << "Q: " << reverse(Q) << '\n';
    cout << "M: " << reverse(M) << '\n';
    //algorithm
    for (int i = 0; i < bits; i++) {
        cout << i + 1 << ") ";
        cout << "A:Q = A:Q << 1: " << reverse(A) << ':'<< reverse(Q) << " ⟶ ";
        //shit left
        char qBit = Q[bits - 1];
        for (int j = bits - 1; j > 0; j--) {
            Q[j] = Q[j - 1];
            A[j] = A[j - 1];
        }
        Q[0] = '0';
        A[0] = qBit;
        cout  << reverse(A) << ':'<< reverse(Q) << " | ";
        //check sign bits
        char signBit = A[bits - 1];
        string ACopy = A;
        if (A[bits - 1] == M[bits - 1]) {
                string t =Negate(M);
                A = AddBinary(A, t);
                cout << "A = A - P = " << reverse(A) << " | ";
        }
        else {
            A = AddBinary(A, M);
            cout << "A = A + P = " << reverse(A) << " | ";
        }
        //check success
        if (signBit == A[bits - 1]) {
            Q[0] = '1';
        }
        else {
            Q[0] = '0';
            A = ACopy;
        }
        cout << endl;
    }
    cout << "Result: Q: " << reverse(Q) << "| (A: "<< reverse(A) << ")\n";
    pair<string, string> res;
    if (dividend * divisor > 0) {
        res.first = Q;
    }
    else {
        res.first = Negate(Q);
    }
    res.second = A;
    cout << "**********\n";
    return res;
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
            if (number[i] != '0') break;
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
