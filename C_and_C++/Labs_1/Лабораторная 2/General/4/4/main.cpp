#include <iostream>
#include <math.h>
#define e 2.71828
using namespace std;

int main()
{
    float k,x1,x2,m;
    cout << "x1= ";
    cin >> x1;
    cout << "x2= ";
    cin >> x2;
    cout << "m=  ";
    cin >> m;
    
    k=pow(cos(pow(x1,2)),3)+pow(sin(pow(x2,3)),2);
    if (k<1)
        cout << "L= " << pow(k,3) + pow(m,0.2) << endl;
    else
        cout << "L= " << pow(k,2)-exp(m) << endl;
    return 0;
}
