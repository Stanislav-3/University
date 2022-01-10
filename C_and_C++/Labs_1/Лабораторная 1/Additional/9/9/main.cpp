//9

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float t, v0, a;
    cout << "t=";
    cin >> t;
    cout << "v0=";
    cin >> v0;
    cout << "a=";
    cin >> a;
    cout << "S=" << v0*t + a*pow(t,2)/2 << endl;
    return 0;
}
