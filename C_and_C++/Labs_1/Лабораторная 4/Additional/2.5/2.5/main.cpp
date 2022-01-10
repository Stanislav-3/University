// 2.5

#include <iostream>

int main(int argc, const char * argv[]) {
    int N,M;
    std::cout << "Enter array dimensions| NxM: ";
    std::cin >> N >> M;
    int ** ar =  new int* [N];
    for (int i=0;i<N;i++)
        ar[i]= new int[M];
    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            std::cin >> ar[i][j];
    for (int i=N-1;i>=0;i--)
        for (int j=M-1;j>=0;j--){
            for (int a=0;a<=i;a++)
                for(int b=0;b<=j;b++)
                    if (ar[a][b]>ar[i][j])
                        ar[i][j]=ar[a][b];
        }
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++)
            std::cout<< ar[i][j]<<" ";
        std::cout << "\n";
    }
    for (int i=0;i<N;i++)
        delete [] ar[i];
    return 0;
}
