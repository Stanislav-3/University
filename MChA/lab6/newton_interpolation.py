import numpy as np
from sympy import symbols, simplify


def y_diff_table(y: list):
    f_diff = np.zeros(shape=(len(y) - 1, len(y) - 1))
    n = f_diff.shape[0]

    for i in range(n):
        f_diff[0, i] = (y[i + 1] - y[i])

    for i in range(1, n):
        for j in range(n-i):
            f_diff[i, j] = f_diff[i - 1, j + 1] - f_diff[i - 1, j]

    return f_diff


def get_a(x: list, y: list):
    a_table = np.zeros(shape=(len(y) - 1, len(y) - 1))
    n = a_table.shape[0]

    for i in range(n):
        a_table[0, i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i])

    for i in range(1, n):
        for j in range(n - i):
            a_table[i, j] = (a_table[i - 1, j + 1] - a_table[i - 1, j]) / (x[i + 1 + j] - x[j])

    return a_table


def newton_poly(x: list, y: list):
    if len(x) != len(y):
        raise ValueError("x & y must have an equal length!")

    poly = 0
    a_table = get_a(x, y)
    for i in range(len(x)):
        if i == 0:
            poly += y[0]
            continue
        x_poly = 1
        for j in range(i):
            x_poly *= (symbols('x') - x[j])

        poly += a_table[i - 1, 0] * x_poly

    return simplify(poly)