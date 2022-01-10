#include <iostream>

void merge(int *arr, int *temp, int l, int m, int r, unsigned long& permutation);
void mergeSort(int* arr, int *temp, int l, int r, unsigned long& permutation);

int main(int argc, const char * argv[]) {
    int N;
    std::cin >> N;
    int* arr = new int[N];
    int* resultArr = new int[N];
    for(int i = 0; i < N; i++) {
        std::cin >> arr[i];
    }
    unsigned long permutation = 0;
    mergeSort(arr, resultArr, 0, N - 1, permutation);
    std::cout << permutation;
    delete [] arr;
    delete [] resultArr;
    return 0;
}

void merge(int* arr, int* temp, int l, int m, int r, unsigned long& permutation)
{
    int i = l, j = m, k = l;
    while (i < m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            k++; i++;
        }
        else {
            temp[k] = arr[j];
            k++; j++;
            permutation += (m - i);
        }
    }
    while (j <= r) {
        temp[k] = arr[j];
        k++; j++;
    }
    while (i < m) {
        temp[k] = arr[i];
        k++; i++;
    }
    for (i = l; i <= r; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort(int* arr, int *temp, int l, int r, unsigned long& permutation)
{
    if (r <= l) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, temp, l, m, permutation);
    mergeSort(arr, temp, m + 1, r, permutation);
    merge(arr, temp, l, m + 1, r, permutation);
}
