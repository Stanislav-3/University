//1

#include <iostream>
using namespace std;

int main()
{
    int i, sum;
    i=1;
    sum=0;
    while (i<=30)
    {
        if (i%2==1)
            sum+=(i-i*i)*(i-i*i);
        else
            sum+= (i/2-i*i*i)*(i/2-i*i*i);
        i++;
    }
    cout << sum << endl;
    return 0;
}
