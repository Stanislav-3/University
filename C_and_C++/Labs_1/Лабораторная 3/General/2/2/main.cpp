//2
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    double d;
    int n;
    n=d=0;
    do
    {
        n++;
        d += pow(0.5, n) + pow (1./3, n);
    } while ( pow(0.5, n) + pow (1./3, n) >= 0.001);
    cout << d << endl;
    return 0;
}
