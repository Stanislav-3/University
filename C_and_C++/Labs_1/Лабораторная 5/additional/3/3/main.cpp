#include <iostream>
#include <math.h>
/*int t;
unsigned long int pow(int a){
    unsigned long int x=1;
    for (int i=0;i<t;i++)
        x*=10;
    return x;
}
unsigned long long int k;
unsigned int f(unsigned long long int n, int r){
    if(n==0 && r==0)
        return 1;
    else
        if(n>0 && r>=0 && r<n*(k-1)+1){
            int x=0;
            for (int i=0;i<k;i++)
                x+=f(n-1,r-i);
            return x;
        }
        else
            return 0;
}

int main(int argc, const char * argv[]) {
    int t;
    unsigned long long int n;
    std::cout<< "Enter k n t: ";
    std::cin>> k>> n>> t;
    int x=0;
    for (int i=0;i<=n*(k-1);i++)
        x+=f(n,i)%pow(t);
    std::cout <<x<<std::endl;
    return 0;
}*/
unsigned long int bpow(unsigned long long int k,unsigned long long int n, int t){
    if (n==0)
        return 1;
    if (n%2 ==1)
        return bpow(k,n-1,t)*k%t;
    else{
        unsigned long long int x=bpow(k,n/2,t)%t;
        return x*x;
    }
}
int main(){
    int t;
    unsigned long long int k,n;
    std::cout<< "Enter k n t: ";
    std::cin>> k>> n>> t;
    t=pow(10,t);
    if(k>0 && n>0 && t>0)
        std::cout<< bpow(k,n,t)%t<< std::endl;
    return 0;
}
