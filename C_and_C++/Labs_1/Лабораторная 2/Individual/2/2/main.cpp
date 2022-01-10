//2

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float x,y;
    cout << "x=";
    cin >> x;
    cout << "y=";
    cin >> y;
    if (x/y>0)
        cout << "s = ln(x) + (|y|)^1/3 = " << log(x) + pow(abs(y),1./3) << endl;
    else
        if (x/y<0)
            cout << "s = ln(|x/y|)*(x+y)^3 = " << log(abs(x/y)) + pow(x+y,3) << endl;
        else
            cout << "s = (x^2+y)^3 = " << pow(x*x + y,3) << endl;
            
    return 0;
}
