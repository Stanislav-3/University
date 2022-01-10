//9
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int G, Y;
    cout << "Enter a birth date\n";
    cin >> G;
    cout << "Enter current year\n";
    cin >> Y;
    Y=Y-G;
    G=Y%10;
    switch (G)
    {
      
        case 1:
            cout << "Человеку " << Y << " год\n";
            break;
        case 2:
        case 3:
        case 4:
            cout << "Человеку " << Y << " года\n";
            break;
        case 0:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            
            cout << "Человеку " << Y << " лет\n";
            break;
    }
    return 0;
}
