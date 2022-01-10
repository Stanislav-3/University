
//  2.4

#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << "Enter matrix dimensions n*m: ";
    int n,m;
    std::cin >> n >> m;
    
    int **a = new int* [n];
    for(int i=0;i<n;i++)
        a[i] = new int [m];
    for (int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            std::cin >> a[i][j];

       for(int i=0;i<n;i++)
           for (int j=0;j<n-i;j++)
               for(int c=0;c<n;c++)
                  for (int b=0;b<n-c;b++)
                    if (a[i][j] < a[c][b]){
                        int temp = a[i][j];
                        a[i][j] = a[c][b];
                        a[c][b] = temp;
                    }
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            std::cout<< a[i][j]<<" ";
        std::cout <<"\n";
    }
    for(int i=0;i<n;i++)
        delete [] a[i];
    return 0;
    for (int i=0;i<n;i++)
          cout<<a[i][m-i-1];
}
