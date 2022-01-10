#include <iostream>
int rec(int n){
    if (n==1) return 1;
    return ((n+1)/2)*((n+1)/2)+rec(n/2);
}
int main(int argc, const char * argv[]) {
    int n;
    std::cout<< "Enter n: ";
    std::cin>> n;
    if (n>0)
        std::cout<<rec(n)<<std::endl;
    else
        std::cout<<"n must be >0\n";
    return 0;
}
