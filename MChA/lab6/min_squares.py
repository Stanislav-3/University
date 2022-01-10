import numpy as np


def sum_of_pow(x, pow):
    n = x.shape[0]
    sum = 0
    for i in range(n):
        sum += np.power(x[i], pow)
    return sum

def sum_x_y_pows(x, y, pow):
    n = x.shape[0]
    sum = 0

    for i in range(n):
        sum += y[i] * np.power(x[i], pow)
    return sum

def min_square(x, y, m):
    if y.shape[0] < m or x.shape[0] != y.shape[0]:
        raise Exception("Size error")
    n = x.shape[0]

    A = np.zeros(shape=(m + 1, m + 1))
    for i in range(m + 1):
        for j in range(m + 1):
            A[i, j] = sum_of_pow(x, i + j)

    b = np.zeros(shape=m + 1)
    for i in range(m+1):
        b[i] = sum_x_y_pows(x, y, i)

    a_vec = np.linalg.solve(A, b)
    return a_vec

def get_best_approx_poly(x, y):
    all_polys = list()
    for i in range(1, x.shape[0]):
            all_polys.append(min_square(x, y, i))
    return all_polys