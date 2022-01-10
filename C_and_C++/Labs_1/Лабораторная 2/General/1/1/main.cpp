#include <iostream>
using namespace std;
int main() {
    int x,y;
    
    cout << "x=";
    cin >> x;
    cout << "y=";
    cin >> y;
    
    if (x==y) {
        x=0;
        y=0;
    }
    else
        if (x>y)
            y=0;
        else
            x=0;
    cout << "x=" << x << " y=" << y << endl;
    
    float A, B, C;
    
    cout << "Enter various values" << endl;
    cout << "A=";
    cin >> A;
    cout << "B=";
    cin >> B;
    cout << "C=";
    cin >> C;
    
    if (A>B&&A>C)
        A=A-0.3;
    else
        if (B>A&&B>C)
            B=B-0.3;
        else C=C-0.3;
    
    cout << "A=" << A << " B= " << B << " C= " << C << endl;
    return 0;
}
