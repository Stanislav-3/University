//17

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {
    cout << "\tx\t|\ty\t\n";
   
    for ( float x=0.4;x<=0.81;x+=0.1)
        cout << setw(9) << left << x << x-x*cos(x) << endl;
    return 0;
}
