//7

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float a,b,c;
    cout << "a=";
    cin >> a;
    cout << "b=";
    cin >> b;
    cout << "c=";
    cin >> c;
    if (b*b-4*a*c>=0)
    {
        cout << "Roots: \n" ;
        if ((-b-sqrt(b*b-4*a*c))/(2*a)>0)
            cout << -sqrt((-b-sqrt(b*b-4*a*c))/(2*a)) << endl << sqrt((-b-sqrt(b*b-4*a*c))/(2*a)) << endl;
        if ((-b+sqrt(b*b-4*a*c))/(2*a)>0)
            cout << -sqrt((-b+sqrt(b*b-4*a*c))/(2*a)) << endl << sqrt((-b+sqrt(b*b-4*a*c))/(2*a)) << endl;
    }
    else
        cout << "There's no roots\n";
    
    return 0;
}
