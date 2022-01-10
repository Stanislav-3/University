#include <iostream>
#include <iomanip>
const int N=2, M=2;
void permutation(float **a){
    for (int i=0;i<N/2;i++)
        for (int j=0;j<M;j++){
            int temp=a[i][j];
            a[i][j]=a[N-1-i][M-1-j];
            a[N-1-i][M-1-j]=temp;
        }
    if (N%2==1){
        for(int j=0;j<M/2;j++){
            int temp=a[N/2][j];
            a[N/2][j]=a[N/2][M-1-j];
            a[N/2][M-1-j]=temp;
        }
    }
}
void zeroelem(float **a){
    int sum=0;
    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            if (a[i][j]==0){
                sum+=1;
                std::cout <<"a["<<i<<"]["<<j<<"]\t";
            }
    if (sum==0)
        std::cout << "there's no such elements\n";
    else
        std::cout << "\nAmount: " << sum <<"\n";
}
int main(int argc, const char * argv[]) {
    float **a=new float* [N];
    for (int i=0;i<N;i++)
        a[i]=new float [M];
    std::cout<<"Enter an array "<<N<<"x"<<M<<std::endl;
    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            std::cin>> a[i][j];
    std::cout << "Elements equals zero are: ";
    zeroelem(a);
    permutation(a);
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++)
            std::cout<<std::setw(5)<<std::left<<a[i][j];
        std::cout<<"\n";
    }
    for(int i=0;i<N;i++)
        delete [] a[i];
    return 0;
}
