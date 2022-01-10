//2

#include <iostream>

int main() {
    std::cout << "Введите число ";
    int num;
    std::cin >> num;
     int k=1;
    for (int i=2; i<num;++i){
       if (num % i ==0)
            k+=i;
    }
    if (k==num)
        std::cout << "число совершенно\n" ;
    else
        std::cout << "число несовершенно\n" ;
    return 0;
}
