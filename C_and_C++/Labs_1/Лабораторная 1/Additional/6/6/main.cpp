//6

#include <iostream>
#include <math.h>

using namespace std;

float x1,u1,x2,u2,x3,u3,a,b,c;
int main()
{
    
    cout << "Enter coordinates of triangle apexes\n";
    cout << "x1="; cin >> x1; cout << "u1="; cin >> u1;
    cout << "x2="; cin >> x2; cout << "u2="; cin >> u2;
    cout << "x3="; cin >> x3; cout << "u3="; cin >> u3;
    a=sqrt(pow(x1-x2,2)+pow(u1-u2,2));
    b=sqrt(pow(x3-x2,2)+pow(u3-u2,2));
    c=sqrt(pow(x1-x3,2)+pow(u1-u3,2));
    cout << "P=" << a+b+c << endl;
    cout << "S=" << sqrt(((a+b+c)/2)*((a+b+c)/2-a)*((a+b+c)/2-b)*((a+b+c)/2-c))<< endl;
    return 0;
}
