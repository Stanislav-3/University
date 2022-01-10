//  Вариант 7

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    double x, p, h, Y, K, C, D;
    cout << "enter variable values\n";
    cout << "x=";
    cin >> x;
    cout << "p=";
    cin  >> p;
    cout << "h=";
    cin >> h;
    cout << "K=";
    cin >> K;
    cout << "C=";
    cin >> C;
    cout << "D=";
    cin >> D;
    
    Y = 0.78 * log(h) + pow(x-p, 3) / (K*C*D);
    cout <<"Y= "<< Y << endl;
    return 0;
}
