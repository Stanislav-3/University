//2

#include <iostream>

using namespace std;

int main()
{   float a, b, c, x, y;
    cout << "Enter brick dimensions a, b, c\n";
    cin >> a >> b >> c;
    cout << "Enter port dimensions x, y\n";
    cin >> x >> y;
    if (x>y)
    {
        x=x+y;
        y=x-y;
        x=x-y;
    }
    again:
    if (a>b)
    {
        a=a+b;
        b=a-b;
        a=a-b;
    }
    if (b>c)
    {
        b=b+c;
        c=b-c;
        b=b-c;
    }
    if (a>b)
        goto again;
    if (a<=x && b<=y)
        cout << "Brick fits\n";
    else
        cout << "Brick doesn't fit\n";
    return 0;
}
