#ifndef SORTINGMETHODS_H
#define SORTINGMETHODS_H
#include <set>
#include <QStack>
#include <QPair>

class SortingMethods
{
public:
    /* Sorting methods */
    static void bubbleSort(int *l, int *r);
    static void shakerSort(int *l, int *r);
    static void combSort(int *l, int *r);
    static void insertionSort(int *l, int *r);
    static void shellsort(int *l, int *r);
    static void treeSort(int *l, int *r);
    static void gnomeSort(int *l, int *r);
    static void selectionSort(int *l, int *r);
    static void heapsort(int *l, int *r);
    static void quickSort(int *l, int *r);
    static void mergeSort(int *l, int *r);
    static void bucketSort(int *l, int *r);
    static void LSDSort(int *l, int *r);
    static void MSDSort(int *l, int *r);
    static void bitonicSort(int *l, int *r);
    static void timsort(int *l, int *r);

private:
    /* For the "heapSort" method */
    template<typename T> class heap;

    /* For the "mergeSort" method */
    static void merge(int *l, int *m, int *r, int *temp);
    static void _mergeSort(int *l, int *r, int *temp);

    /* For the "bucketSort" method */
    static void _newBucketSort(int *l, int *r, int *temp);

    /* For the "_LSDSort" & "_MSDSort" methods */
    static int digit(int n, int k, int N, int M);

    /* For the "LSDSort" method */
    static void _LSDSort(int *l, int *r, int N);

    /* For the "MSDSort" method */
    static void _MSDSort(int *l, int *r, int N, int d, int *temp);

    /* For the "bitonicSort" method */
    static void makebitonic(int *l, int *r);
    static void bitseqsort(int *l, int *r, bool inv);

    /* For the "timSort" method */
    static void _timSort(int *l, int *r, int *temp);
};

#endif // SORTINGMETHODS_H
