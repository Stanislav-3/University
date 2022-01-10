//
#include <iostream>
#include <iomanip>
int main() {
    std::cout << "Введите размерность матрицы NxM:\n";
//    int N,M;
//    std::cin >> N >> M;
    int a[2][2]={1,2,3,4};
//    srand(time(0));
    for (int i=0;i<2;i++){
        for (int j=0;j<2;j++){
//            a[i][j]=rand()%100-50;
            std::cout<<std::setw(3)<<a[i][j]<<" ";
        }
        std::cout << "\n";
    }
    int k=0;
    for (int i=0;i<2;i++)
        for (int j=1+i;j<2;j++)
            if (a[i][j]<0)
                k+=1;

    std::cout << "Количество отрицательных элементов выше главной диагонали =" << k << "\n";
    return 0;
}
