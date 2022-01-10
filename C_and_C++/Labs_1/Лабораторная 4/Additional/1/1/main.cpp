//2
#include <iostream>

int main() {
    std::cout << "Enter array dimension: ";
    int x,y;
    std::cin >> x >> y;
    int **p_arr = new int *[x];
    for (int i=0 ; i<x; i++){
        p_arr[i]= new int [y];
    }
    for (int i=0;i<x;i++){
        for (int j=0;j<y;j++){
            std::cin >> p_arr[i][j];
        }
    }
    std::cout << "\n";
    for (int i=0;i<x;i++)
        for (int j=1;j<y;j++)
            for (int n=0;n<y-j;n++)
                if (p_arr [i][n] < p_arr[i][n+1]){
                   int temp = p_arr [i][n];
                   p_arr [i][n] = p_arr[i][n+1];
                   p_arr [i][n+1] = temp;
                }
    int *y1 = new int [x];
    for (int i=0;i<x;i++)
        y1[i]=y;
    for (int i=0;i<x;i++){
        for (int j=1;j<y1[i]-1;j++){
            if (p_arr[i][j-1] == p_arr[i][j] || p_arr[i][j] == p_arr[i][j+1])
                continue;
            else{
                for (int n=j;n<y1[i]-1;n++)
                    p_arr[i][n] = p_arr[i][n+1];
                j--;
                y1[i]--;
            }
        }
        if (p_arr[i][0] !=p_arr[i][1]){
            for (int n=0;n<y1[i]-1;n++)
                p_arr[i][n] = p_arr[i][n+1];
            y1[i]--;
        }
        if (p_arr[i][y1[i]-1] !=p_arr[i][y1[i]-2])
            y1[i]--;
    }
//
        for (int i=0;i<x;i++){
        for (int j=0;j<y1[i];j++)
            std::cout<<p_arr[i][j]<<" ";
        std::cout << "\n";
//
    }
    std::cout << "Строка матрицы длина максимальной серии которой минимальна: ";
    int k=0;
    for (int i=0; i<x; i++){
        int min=0;
        for (int n=1;p_arr[i][n] == p_arr[i][n-1];n++){
            min = n+1;
            if (n == y1[i]-1)
                break;
        }
        int sum=1, count=min;
        while (count<y1[i]-1){
            if(p_arr[i][count] == p_arr[i][count+1]){
                sum++;
                count++;
            }
            else{
                if (sum <= min){
                    min=0;
                    break;
                }
                sum=1;
                count++;
            }
        }
        if (sum <= min)
            min=0;
        if (min != 0)
            std::cout << i+1 <<" ";
        else k+=1;
    }
    if (k==x)
        std::cout << "Такой строки нет\n";
    
    int **arr =new int *[x];
    for (int i=0;i<x;i++)
        arr[i]= new int [y1[i]];
    for (int i=0;i<x;i++){
        for (int j=0;j<y1[i];j++){
            arr[i][j]=p_arr[i][j];
            std::cout<<arr[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    for (int i=0;i<x;i++)
        delete [] arr[i];
    delete [] y1;
    for (int i=0;i<x;i++)
        delete [] p_arr[i];
    
    return 0;
    }
