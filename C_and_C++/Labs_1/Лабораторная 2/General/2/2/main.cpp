#include <iostream>
using namespace std;

int main()
{
    float a,b;
    char zn;
    
label:
    cout << "Enter expression\n";
    cin >> a >> b;
    cin >> zn;
    if (zn=='y')
        goto label;
    switch (zn)
    {
        case '+':
        {
            cout << "d = " << a+b << endl;
            break;
        }
        case '-':
        {
            cout << "d = " << a-b << endl;
            break;
        }
        case '*':
        {
            cout << "d = " << a*b<< endl;
            break;
        }
        case '/':
        {
            cout << "d = " << a/b << endl;
            break;
        }
        default:
        {
            cout << "Неправильный ввод\nВведите значение 'zn' повторно\n";
            goto label;
        }
    }
    
    return 0;
    x>y?t=6:t=8;
}
