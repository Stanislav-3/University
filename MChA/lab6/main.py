import numpy as np
import re
from lagrange_interpolation import lagrange_poly
from newton_interpolation import newton_poly
from sympy import symbols, simplify
from min_squares import min_square, get_best_approx_poly
import matplotlib.pyplot as plt

k = 6
m = 3
x = np.array([0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1])
p = np.array([0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01])

x = np.array([0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1])
p = np.array([0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.3, 2.55, 2.79, 3.01])
x *= 10
x **= 2

y = p + (-1)**k * m

y *= 15
point = 90


def output_poly(poly, size = 65):
    poly_parts = str(poly.copy()).split(" ")
    count = 0

    for i in range(len(poly_parts)):
        count += len(poly_parts[i])
        if count >= size:
            print()
            count = 0
        print(poly_parts[i], end="")
    print()

def get_koeff(poly):
    s = re.split(r"[ + *x**]+", str(poly.copy()))
    ans = []
    neg = False
    for i in range(len(s)):
        if s[i] == '-':
            neg = True
        if s[i].find('.') >= 0:
            if neg == True:
                ans.append(-1 * float(s[i]))
                neg = False
            else:
                ans.append(float(s[i]))
    return ans

# plotting lagrange and newton poly
def plot_iterpolation(kind):
    fig = plt.figure(figsize=(8, 6))
    plt.plot(x, y, 'ko', color='red')

    poly_lagrange = np.polynomial.polynomial.Polynomial(get_koeff(lagrange)[::-1])
    poly_newton = np.polynomial.polynomial.Polynomial(get_koeff(newton)[::-1])

    # l = np.linspace(-1.5, 1.5)
    l = np.linspace(-5, 105)
    if kind == "Newton":
        fig.suptitle('Newton interpolation polynomial')
        plt.plot(l, poly_newton(l), color='blue')
    elif kind == "Lagrange":
        fig.suptitle('Lagrange interpolation polynomial')
        plt.plot(l, poly_lagrange(l), color='darkgreen')

    # plt.ylim(-2, 10)
    # plt.xlim(-0.5, 1.5)
    plt.xlim(-5, 105)
    plt.ylim(40, 105)
    plt.grid()
    plt.axvline(color="black", linewidth=0.5)
    plt.axhline(color='black', linewidth=0.5)
    plt.show()

if __name__ == '__main__':
    print('**************')
    print(f"*Initial data:\nx = {x}\n"
          f"y = {y}")
    print('--------------\n')


    print('***********************************')
    lagrange = lagrange_poly(x, y)
    print(f'*Lagrange interpolation polynomial:\n'
          f'L(x): ', end="\n\n")
    print(np.poly1d(get_koeff(lagrange)))
    print(f'*Interpolation point: x = {point}\n'
          f'L({point}) = {float(lagrange.subs(symbols("x"), point))}')
    print('-----------------------------------\n')


    print('*********************************')
    newton = newton_poly(x, y)
    print(f'*Newton interpolation polynomial:\n'
          f'N(x): ', end="\n\n")
    print(np.poly1d(get_koeff(newton)))
    print(f'*Interpolation point: x = {point}\n'
          f'N({point}) = {float(newton.subs(symbols("x"), point))}\n')
    print('---------------------------------\n')


    print('**********************************')
    print(f'*Polynomials of best approximation:')
    all_best = get_best_approx_poly(x, y)
    for i in range(len(all_best)):
        print(f"P{i + 1}:\n" , np.poly1d(all_best[i][::-1]))
        print(f"P{i + 1}({point}) = ", np.polyval(all_best[i][::-1] , point))
        print()
    print('-----------------------------------\n')

    plot_iterpolation("Lagrange")
    plot_iterpolation("Newton")

    # plotting poly's of best approximation
    fig = plt.figure(figsize=(8, 6))
    fig.suptitle('Polynomials of best approximation')
    for i, koef in enumerate(all_best):
        col = ""
        if i == 0:
            col = 'slateblue'
        elif i == 1:
            col = 'indigo'
        elif i == 2:
            col = 'darkviolet'
        elif i == 3:
            col = 'violet'
        elif i == 4:
            col = 'brown'
        elif i == 5:
            col = 'gold'
        elif i == 6:
            col = 'cyan'
        elif i == 7:
            col = 'olive'
        elif i == 8:
            col = 'crimson'
        else:
            col = 'magenta'
        poly = np.polynomial.polynomial.Polynomial(koef)
        # l = np.linspace(-5, 5)
        l = np.linspace(-5, 105)
        plt.plot(l, poly(l), color=col)
    plt.plot(x, y, 'ko', color='black')
    # plt.ylim(-2, 10)
    # plt.xlim(-5, 5)
    plt.xlim(-5, 105)
    plt.ylim(40, 105)
    plt.grid()
    plt.axvline(color="black", linewidth=0.5)
    plt.axhline(color='black', linewidth=0.5)
    plt.show()

