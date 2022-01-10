//  2.3

#include <iostream>
#include <iomanip>
int main(int argc, const char * argv[]) {
    std::cout << "Enter matrix dimensions N: ";
    int N;
    std::cin >> N;
    
    int **a = new int* [N];
    for(int j=0;j<N;j++)
        a[j] = new int [N];
    int i=0;
    for (int k=0;k<N;k++){
        for(int j=k;j<N-k;j++)
            a[k][j]= ++i;
        for(int j=k+1;j<N-k;j++)
            a[j][N-k-1]= ++i;
        for(int j=N-k-2;j>=k;j--)
            a[N-k-1][j]= ++i;
        for(int j=N-k-2;j>k;j--)
            a[j][k]= ++i;
    }
    for (int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            std::cout <<std::setw(3)<< a[i][j];
        std::cout <<"\n";
    }
    for(int i=0;i<N;i++)
        delete [] a[i];
    return 0;
}
