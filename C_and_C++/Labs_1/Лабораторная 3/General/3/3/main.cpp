//3

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    float X, B, A, M;
    int i;
    M= 20;
    B= M_PI/2;
    A= 0;
    cout << "|\t\tx\t\t|\t\ty\t\t|\n";
    for (i=0; X<B; i++)
    {
        X=A+i*(B-A)/M;
        cout << "\t" <<setw(10)<<left<< X << "\t\t"<< sin(X)-cos(X)<<endl;
    }
        return 0;
}
