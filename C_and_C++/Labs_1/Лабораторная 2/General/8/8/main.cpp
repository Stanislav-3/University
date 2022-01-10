//8
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int N, k;
    cout << "Enter N<20\n";
    cin >> N;
    cout << "Enter k<80\n";
    cin >> k;
    N=N+k;
    k=N%10;
    
    switch (k)
    {
        case 1:
            cout << "N= " << N << " рубль\n" ;
            break;
        case 2:
        case 3 :
            cout << "N= " << N << " рубля\n" ;
            break;
        case 0:
        case 5:
        case 7:
        case 8:
        case 9:
            cout << "N= " << N << " рублей\n" ;
            break;
    }
    return 0;
}
