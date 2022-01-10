import random


def quick_sort(arr, l, r):
    if r - l <= 1:
        return

    d = (random.randint(l, r - 1))
    mid = arr[d]

    i, j = l, r - 1
    while i <= j:
        while i < r and arr[i] < mid:
            i += 1
        while j >= l and arr[j] > mid:
            j -= 1
        if i <= j:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1
            j -= 1

    quick_sort(arr, l, i)
    quick_sort(arr, i, r)