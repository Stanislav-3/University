//2

#include <iostream>
int main() {
    std::cout << "Введите размерность матрицы AxA:";
    int A;
    std::cin >> A;
    int **a=new int* [A];
    for (int i=0;i<A;i++)
        a[i]=new int[A];
    srand(time(0));
    for (int i=0;i<A;i++){
        for (int j=0;j<A;j++){
            a[i][j]=rand()%100;
            std::cout<<a[i][j]<<" ";
        }
        std::cout << "\n";
    }
    std::cout << "Ответ: \n";
    
    int **a_=new int *[A];
    for (int i=0;i<A;i++)
        a_[i]=new int [A];
    for (int i=0;i<A;i++)
        for (int j=0;j<A;j++)
            a_[i][j]=0;
    
    for (int i=0;i<A;i++){
        for (int j=0;j<A;j++){
            for (int p=0;p<A;p++)
               a_[i][j]+=a[i][p]*a[p][j];
        }
    }
    for (int i=0;i<A;i++)
        delete [] a[i];
    for (int i=0;i<A;i++){
        for (int j=0;j<A;j++)
           std::cout << a_[i][j] <<" ";
        std::cout << "\n";
        
    }
    for (int i=0;i<A;i++)
    delete [] a_[i];
   
    return 0;
}
