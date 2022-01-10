//7

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    float a, b, c;
    cout << "Enter a, b ,c\n";
    cin >> a >> b >>c;
    
    cout << "h(a)= " << (sqrt(((a+b+c)/2)*((a+b+c)/2-a)*((a+b+c)/2-b)*((a+b+c)/2-c)))*2/a << endl;
    return 0;
}
