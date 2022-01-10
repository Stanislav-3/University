//5
#include <iostream>

using namespace std;

int main()
{
    float x,y;
    cout << "Enter (x,y)\n";
    cin >> x >> y;
    if (x*x+(y-2)*(y-2)<4 && y<1-x*x)
        cout << "u= " << x-y << endl;
    else
        cout << "u= " << x*y+5 << endl;
}
