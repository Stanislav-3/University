# coding=utf-8
import numpy as np

k = 6
C = np.array([[0.2, 0, 0.2, 0, 0],
              [0, 0.2, 0, 0.2, 0],
              [0.2, 0, 0.2, 0, 0.2],
              [0, 0.2, 0, 0.2, 0],
              [0, 0, 0.2, 0, 0.2]])
D = np.array([[2.33, 0.81, 0.67, 0.92, -0.53],
              [-0.53, 2.33, 0.81, 0.67, 0.92],
              [0.92, -0.53, 2.33, 0.81, 0.67],
              [0.67, 0.92, -0.53, 2.33, 0.81],
              [0.81, 0.67, 0.92, -0.53, 2.33]])
A = k * C + D

x = np.zeros(5)
b = [4.2, 4.2, 4.2, 4.2, 4.2]

# Метод Гаусса (схема единственного деления)
def gaussian_elimination_1(A: np.array, b: np.array):
    A = A.copy()
    b = b.copy()
    rows = len(A)
    columns = len(A[0])
    for k in range(columns):
        if A[k][k].astype(np.int32) == 0:
            return f"Метод Гаусса (схема единственного деления) использоватль нельзя т.к. A[{k}][{k}] = 0"
        for i in range(k + 1, rows):
            q = A[i][k] / A[k][k]
            for j in range(k, columns):
                A[i][j] = A[i][j] - q * A[k][j]
            b[i] = b[i] - q * b[k]

    n = rows - 1
    x[n] = b[n] / A[n][n]
    for k in range(n - 1, -1, -1):
        sum = 0
        for i in range(k + 1, columns):
            sum = sum + x[i] * A[k][i]
        x[k] = (b[k] - sum) / A[k][k]
    return x


# Метод Гаусса с выбором главного элемента по столбцу (схема частичного выбора)
def gaussian_elimination_2(A: np.array, b: np.array):
    A = A.copy()
    b = b.copy()
    rows = len(A)
    columns = len(A[0])
    for k in range(columns):
        max_i = k
        for t in range(k, rows):
            if np.math.fabs(A[k][k]) < np.math.fabs(A[t][k]):
                max_i = t
        t = A[k].copy()
        A[k] = A[max_i].copy()
        A[max_i] = t
        t = b[k]
        b[k] = b[max_i]
        b[max_i] = t

        for i in range(k + 1, rows):
            q = A[i][k] / A[k][k]
            for j in range(k, columns):
                A[i][j] = A[i][j] - q * A[k][j]
            b[i] = b[i] - q * b[k]

    n = rows - 1
    x[n] = b[n] / A[n][n]
    for k in range(n - 1, -1, -1):
        sum = 0
        for i in range(k + 1, columns):
            sum = sum + x[i] * A[k][i]
        x[k] = (b[k] - sum) / A[k][k]
    return x


# Метод Гаусса с выбором главного элемента по всей матрице (схема полного выбора)
def gaussian_elimination_3(A: np.array, b: np.array):
    A = A.copy()
    b = b.copy()
    rows = len(A)
    columns = len(A[0])
    for k in range(rows - 1):
        # Pivot
        max_i = abs(A[k:, k]).argmax() + k
        # Swap
        if max_i != k:
            t = A[k].copy()
            A[k] = A[max_i].copy()
            A[max_i] = t
            t = b[k]
            b[k] = b[max_i]
            b[max_i] = t
        # Eliminate
        for row in range(k + 1, rows):
            q = A[row, k] / A[k, k]
            A[row, k:] = A[row, k:] - q * A[k, k:]
            b[row] = b[row] - q * b[k]

    n = rows - 1
    x[n] = b[n] / A[n][n]
    for k in range(n - 1, -1, -1):
        sum = 0
        for i in range(k + 1, columns):
            sum = sum + x[i] * A[k][i]
        x[k] = (b[k] - sum) / A[k][k]
    return x


if __name__ == '__main__':
    eps = pow(10, -4)
    print("A:\n", A, end="\n\n")
    print("b:\n", b, end="\n\n")
    print("Ответ полученный используя встроенные библиотеки:\n", np.linalg.solve(A, b), end="\n\n")
    print("Метод Гаусса (схема единственного деления):")
    ans = gaussian_elimination_1(A, b)
    if not isinstance(ans, str):
        print((gaussian_elimination_1(A, b) / eps).astype(np.int32) * eps)
    else:
        print(ans)
    print()
    print("Метод Гаусса с выбором главного элемента по столбцу (схема частичного выбора):\n", \
          (gaussian_elimination_2(A, b) / eps).astype(np.int32) * eps, end="\n\n")
    print("Метод Гаусса с выбором главного элемента по всей матрице (схема полного выбора):\n", \
          (gaussian_elimination_3(A, b) / eps).astype(np.int32) * eps, end="\n\n")
