from sympy import symbols, simplify

def l_i(x, x_j):
    ans = 1
    for i in range(len(x)):
        if x_j != x[i]:
            ans *= (symbols('x') - x[i]) / (x_j - x[i])
    return ans


def lagrange_poly(x: list, y: list):
    if len(x) != len(y):
        raise ValueError("x & y must have an equal length!")

    poly = 0
    for i in range(len(x)):
        poly += y[i] * l_i(x, x[i])
    return simplify(poly)