#include <iostream>
using namespace std;
void divide (long long int, long long int);
int main(int argc, const char * argv[]) {
    cout<<"Введите число: ";
    int x;
    cin>>x;
    divide(x,5);
    divide(x,47);
    divide(x,89);
    return 0;
}
void divide(long long a,long long b){
    long long d=1;
    if (a<=0 && b<=0){
        a=abs(a);
        b=abs(b);
    } else if (a<0 || b<0){
        d=-1;
        a=abs(a);
        b=abs(b);
    }
    for(int i=32;i>=0;i--){
        long long int current=(b<<i);
        if (a>=current){
            a-=current;
        }
    }
    if (a!=0) cout<<"не делится\n";
    else cout<<"делится\n";
}
