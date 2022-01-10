//2
#include <iostream>

int main() {
    int k;
    std::cout << "Введите количество элементов массива: ";
    std::cin >> k;
    int a[k];
    for (int i=0;i<k;i++)
        std::cin >> a[i];
    for (int i=0; i<k/2;i++){
        int pl;
        pl=a[i];
        a[i]=a[k-1-i];
        a[k-1-i]=pl;
        
    }
    for (int i=0;i<k;i++)
         std::cout << a[i] << " ";
    std::cout << "\n";
    return 0;
}
