#include <iostream>
float F(int);
float S(int, int);
int main(int argc, const char * argv[]) {
    int p,q;
    std::cout<< "Enter p and q\n";
    std::cin>> p >> q;
    if (p>=0 && q>=p)
        std::cout<<S(p,q)<<"\n";
    return 0;
}
float F(int i){
    if (i%10>0)
        return i%10;
    else
        if (i==0)
            return 0;
        else
            return F(i/10);
}
float S(int p,int q){
    int sum=0;
    for (int i=p;i<=q;i++)
        sum+=F(i);
    return sum;
}
