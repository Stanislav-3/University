//11

#include <iostream>
#include <math.h>

using namespace std;

int main()
{

    cout << "Enter rectangle sides\n";
    float a,b;
    cout << "a=";
    cin >> a;
    cout << "b=";
    cin >> b;
    
    cout << "P= " << 2*(a+b) << endl << "S= " << a*b << endl << "Diagonal= " << sqrt( pow(a,2) + pow(b,2) ) << endl;
    return 0;
}
