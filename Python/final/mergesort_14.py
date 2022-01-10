def merge_sort(arr, l=0, r=None):
    if r is None:
        r = len(arr)

    if r - l <= 1:
        return

    d = (l + r) // 2
    merge_sort(arr, l, d)
    merge_sort(arr, d, r)

    i, j = l, d
    sorted_arr = []
    while i < d or j < r:
        if i != d and (j == r or arr[i] <= arr[j]):
            sorted_arr.append(arr[i])
            i += 1
        else:
            sorted_arr.append(arr[j])
            j += 1

    for i in range(l, r):
        arr[i] = sorted_arr[i - l]