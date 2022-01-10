#include <iostream>

using namespace std;

int main()
{
    float a,b,c,d;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    cout << "d = ";
    cin >> d;
    if (d <= c && d > a)
        cout << "Z = \n" << a+b/c;
    else
        if (d > c && d <= a)
            cout << "Z = \n" << a-b/c;
        else cout << "Z = 0\n";
    return 0;
}
