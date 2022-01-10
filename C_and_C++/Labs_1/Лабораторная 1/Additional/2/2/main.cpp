//2

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int a, b;
    cout << "input two natural numbers\n1";
    cin >> a >> b;
    
    cout << "min= " << ((a+b)-abs(a-b))/2 << " max= " << ((a+b)+abs(a-b))/2 << endl;
    return 0;
}
