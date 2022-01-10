//10

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float a,b,c;
    
    cout << "Enter triangle sides\n";
    cout << "a=";
    cin >> a;
    cout << "b=";
    cin >> b;
    cout << "c=";
    cin >> c;
    
    cout << "S=" << sqrt(((a+b+c)/2)*((a+b+c)/2-a)*((a+b+c)/2-b)*((a+b+c)/2-c))<< endl;
    return 0;
}
