//6

#include <iostream>

using namespace std;

int main()
{
    float a, b ,c;
    int N;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "c = ";
    cin >> c;
    cout << "N = ";
    cin >> N;
    switch (N)
    {
    case 2:
            cout << "Y = " << b*c-a*a << endl;
            break;
    case 56:
            cout << "Y = " << b*c << endl;
            break;
    case 7:
            cout << "Y = " << a*a + c << endl;
            break;
    case 3:
            cout << "Y = " << a - b*c << endl;
            break;
        default:
            cout << "Y=" << (a+b)*(a+b)*(a+b) << endl;
    }
    return 0;
}
