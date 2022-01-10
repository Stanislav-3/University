import math
import numpy as np
import matplotlib.pyplot as plt
import sturm_method as sturm_m
import bisection_method as b_m
import secant_method as s_m
import newton_method as n_m
import func

l, r = -10, 10

a = 20.2374
b = -131.210
c = -843.923

def val(num):
    if num < 0:
        return f"- {math.fabs(num)}"
    else:
        return f"+ {num}"

def graph(poly, x):
    Y = []
    for i in range(len(x)):
        y = 0
        for j in range(len(poly)):
            y += poly[j] * x[i] ** (len(poly) - j -1)
        Y.append(y)
    return Y

if __name__ == '__main__':
    poly = [1, a, b, c]
    print(f"Equation: {val(poly[0])}x^3 {val(poly[1])}x^2 {val(poly[2])}x {val(poly[3])} = 0")

    print("Amount of roots on [-10, 10]: ", sturm_m.count_roots(poly, -10, 10))

    x = np.linspace(-26, 10, 300, endpoint=True)
    plt.plot(x, graph(poly, x))
    plt.plot(np.linspace(-26, 10, 50, endpoint=True), np.zeros(50))
    plt.show()

    print("Roots(via numpy): ", np.roots(poly))

    print("Borders: ", end="")
    func.get_border(poly, -30, 10)

    eps = 0.0001
    bisection_method = b_m.bisection_method(poly, -30, -24, eps)
    secant_method = s_m.secant_method(poly, -30, -24, eps)
    newton_method = n_m.newton_method(poly, -30, -24, eps)

    print("Bisection method| root: ", bisection_method[0], "| iterations: ", bisection_method[1])
    print("Secant method| root: ", secant_method[0], "| iterations: ", secant_method[1])
    print("Newton method| root: ", newton_method[0], "| iterations: ", newton_method[1])

