//1

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int h1, h2, min1, min2;
    
    cout << "Enter the time when student started doing his tasks\n";
    cin >> h1 >> min1;
    cout << "Enter the time when student finished doing his tasks\n";
    cin >> h2 >> min2;
    
    if (h2>=h1)
        cout << "It took " << (60*(h2-h1)+min2-min1)/60 << " hours and " << (60*(h2-h1)+min2-min1)%60 << " minutes\n";
    else
        cout << "It took " << ((23+h2-h1)*60+60+min2-min1)/60 << " hours and " << ((23+h2-h1)*60+60+min2-min1)%60 << " minutes\n";
    
    return 0;
}
