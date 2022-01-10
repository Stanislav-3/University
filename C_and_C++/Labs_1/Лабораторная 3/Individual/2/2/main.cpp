//2

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    cout << "На сколько частей вы желаете разбить отрезок: ";
    int n;
    cin >> n;
    float x=2, x0=2, min=abs(log(x)+3*tan(x)+pow(x,1/2));
    while (x<4)
    {
        if (min > abs(log(x)+3*tan(x)+pow(x,1/2)))
        {
            min=abs(log(x)+3*tan(x)+pow(x,1/2));
            x0=x;
        }
        x+=2./n;
    }
    cout << "Корень уравнения = " << x0 << endl;
    return 0;
}
