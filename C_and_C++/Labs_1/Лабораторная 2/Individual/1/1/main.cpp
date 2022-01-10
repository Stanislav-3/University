//1

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float z,x,a;
    int o;
    cout << "z=";
    cin >> z;
    cout << "a=";
    cin >> a;
    if (z >=1)
        x=z+1;
    else
        x=z*z;
    cout << "Choose the function:\n" << "1) 2x\t" << "2) x^2\t" << "3) x/3\n" << "Function number\t";
    cin >> o;
    switch (o)
    {
        case 1:
            cout << "y= a*ln(1+x^(1/5))+cos(2*x+1)^2 = " << a*log(1+pow(x,1/5))+pow(cos(2*x+1),2)<<endl;
            break;
        case 2:
            cout << "y= a*ln(1+x^(1/5))+cos(x^2+1)^2 = " << a*log(1+pow(x,1/5))+pow(cos(x*x+1),2)<<endl;
            break;
        case 3:
            cout << "y= a*ln(1+x^(1/5))+cos(x/3+1)^2 = " << a*log(1+pow(x,1/5))+pow(cos(x/3+1),2)<<endl;
            break;
        default:
            cout << "ERROR\n";
    }
        
    return 0;
}
