//6
#include <iostream>

int factorial (int x){
    if (x==0)
        return 1;
    else
        return x=x*factorial(x-1);
}
int main() {
   
    for (int i=100;i<1000;++i){
        if ((factorial(i%10)+factorial(i/10%10)+factorial(i/100))==i)
            std::cout << i << "\n";
    }
    return 0;
}
