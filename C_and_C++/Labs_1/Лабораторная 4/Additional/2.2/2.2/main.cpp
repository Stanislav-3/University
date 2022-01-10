//  2.2

#include <iostream>
#include <iomanip>
int main(int argc, const char * argv[]) {
    std::cout << "Введите порядок кратный четырем: ";
    int n;
    std::cin >> n;
    int **sq = new int* [n];
    for (int i=0;i<n;i++)
        sq[i] = new int [n];
    
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            sq[i][j]= n*i+j+1;
    
    std::cout <<"\n";
    int **fsq = new int* [n];
    for (int i=0;i<n;i++)
        fsq[i] = new int [n];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            fsq[i][j]=sq[n-1-i][n-1-j];
    
    for (int i=0;i<=n/4-1;i++)
        for (int j=0;j<=n/4-1;j++)
            fsq[i][j]=sq[i][j];
    for (int i=3*n/4;i<n;i++)
        for (int j=3*n/4;j<n;j++)
            fsq[i][j]=sq[i][j];
    for (int i=3*n/4;i<n;i++)
        for (int j=0;j<=n/4-1;j++)
            fsq[i][j]=sq[i][j];
    for (int i=0;i<=n/4-1;i++)
        for (int j=3*n/4;j<n;j++)
            fsq[i][j]=sq[i][j];

    for (int i=n/2-1;i<n/2+1;i++)
    for (int j=n/2-1;j<n/2+1;j++)
        fsq[i][j]=sq[i][j];

    for (int i=0;i<n;i++){
    for (int j=0;j<n;j++)
        std::cout << std::setw(3)<<std::left<< fsq[i][j];
    std::cout << "\n";
    }
    for (int i=0;i<n;i++)
        delete [] sq[i];
    for (int i=0;i<n;i++)
        delete [] fsq[i];
    return 0;
}
