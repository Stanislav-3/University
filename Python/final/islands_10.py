def mark(arr, i, j):
    arr[i][j] = 0

    if i > 0:
        if arr[i - 1][j] == 1:
            mark(arr, i-1, j)

    if i < len(arr) - 1:
        if arr[i + 1][j] == 1:
            mark(arr, i+1, j)

    if j > 0:
        if arr[i][j - 1] == 1:
            mark(arr, i, j - 1)

    if j < len(arr[0]) - 1:
        if arr[i][j + 1] == 1:
            mark(arr, i, j + 1)


def islands(arr):
    count = 0
    for i in range(len(arr)):
        for j in range(len(arr[0])):
            if arr[i][j] == 1:
                count += 1
                mark(arr, i, j)
    return count


arr = [
    [1, 0, 1, 1, 0],
    [1, 1, 1, 1, 1],
    [0, 0, 0, 0, 0],
    [1, 1, 0, 1, 1],
]

print(islands(arr))