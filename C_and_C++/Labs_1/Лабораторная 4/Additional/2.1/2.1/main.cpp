//  2.1

#include <iostream>

int main(int argc, const char * argv[]) {
    int N,M;
    std::cout << "Enter matrix dimensions\tN*M: ";
    std::cin >> N >> M;
    
    int **a = new int *[N];
    for (int i=0 ; i<N; i++)
        a[i]= new int [M];
    for (int i=0 ; i<N; i++)
        for (int j=0 ; j<M; j++)
            std::cin >> a[i][j];
    int *c = new int [M];
    for (int i=0 ; i<N; i++)
        c[i]=M;
    for (int i=0 ; i<N; i++)
        for (int j=0 ; j<c[i]; j++){
            int d=0;
            for (int k=0 ; k<c[i]; k++)
                if (a[i][j] == a[i][k])
                    d+=1;
            if (d==1){
                for (int k=j;k<c[i]-1;k++)
                    a[i][k] = a[i][k+1];
                    j--;
                    c[i]--;
            }
        }
    for (int i=0 ; i<N; i++){
        for (int j=0 ; j<c[i]; j++)
            std::cout << a[i][j]<<" ";
        std::cout << "\n";
        }
    delete [] c;
    for (int i=0;i<N;i++)
        delete [] a[i];
    return 0;
}
