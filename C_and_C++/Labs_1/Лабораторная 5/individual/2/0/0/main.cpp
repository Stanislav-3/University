#include <iostream>
const int N=8;
int X[N];

void rec(int l,int r){
    if (l==r){
        if(не промежуток)
            std::cout<<"не выполн";
        return;
    }
    rec(l,(l+r)/2);
    rec((l+r)/2+1,r);
}
int main(int argc, const char * argv[]) {
    for (int i=0;i<N;i++)
        std::cin>>X[i];
    rec(0,N-1);
    return 0;
}
