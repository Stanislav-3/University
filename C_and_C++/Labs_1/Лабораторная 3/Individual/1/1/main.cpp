//2
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int n, k;
    cout <<"Введите количество членов ряда: ";
    cin >> n;
    cout <<"Введите количество чисел от коротых желаете посчитать функцию: ";
    cin >> k;
    for (int i=0;i<k;i++)
    {
        cout << "Введите значения x: ";
        float x;
        cin >> x;
        float s=1;
        for ( int j=1;j<=n;j++)
        {
//            факториал
            float f=1;
            for (int c=1;c<=2*j;c++)
                f*=c;
            s+=pow(x,j*2)/(f);
        }
        cout << "S(x): " << s << "\nY(x): " << (exp(x)+exp(-x))/2 << endl;
    }
    return 0;
}

