from matplotlib import pylab
from scipy.integrate import odeint as od
import numpy as np
import logging


a_ = 0
b_ = 1
x_0 = 0
y_0 = 0
eps = 0.001

m = 1.0
a = 1.3


def to_fixed(value, digits=0):
    if isinstance(value, list):
        return [to_fixed(i, digits) for i in value]

    return f"{value:.{digits}f}"


def f(y, x):
    return (a * (1 - y ** 2)) / ((1 + m) * (x ** 2) + (y ** 2) + 1)


def exact_points(step, X):
    exact_points = []
    for x in X:
        r2 = exact(x)
        exact_points.append(r2)
    return exact_points


def adams_r(step):
    y1 = y_0
    xlist = np.arange(a_, b_ + step, step)
    exact_point = exact_points(step, xlist)
    adams_points = []
    adams_points.append(y1)
    adams_points.append(exact_point[1])
    for i in range(1, len(xlist) - 1, 1):
        y1 = adams(xlist[i], adams_points[i], xlist[i - 1], adams_points[i - 1], step)
        adams_points.append(y1)
    sum = 0
    for i in adams_points:
        sum += i
    return i


def find_step():
    h0 = eps ** (1 / 4)
    n = int((b_ - a_) // h0)

    if n % 2 != 0:
        n += 1

    while check_step(n, eps):
        n = n // 4 * 2

    while not check_step(n, eps):
        n *= 2

    return (b_ - a_) / n


def check_step(n, epsilon):
    h = (b_ - a_) / n
    y2_1 = adams_r(h)
    y2_2 = adams_r(h * 2)
    delta = (1 / 15) * abs(y2_1 - y2_2)
    return delta < epsilon


def adams(x1, y1, x2, y2, step):
    return (y1 + step * ((3 / 2) * f(y1, x1) - (1 / 2) * f(y2, x2)))


def exact(x):
    sol = od(f, y_0, [a_, x])
    return sol[1][0]


def show(l1, l2):
    print(34 * '*')
    print('* Мeтод Адамса | Точное значение *')
    for i in range(len(l1)):
        print('*   ', l1[i], '   |     ', l2[i], '\t *')
    print(34 * '*')


if __name__ == "__main__":
    print(f'Исходные данные: {a:.1f}(1 - y²) / ({1 + m:.1f}x² + y² + 1))')
    print(f'Интервал [{a_}, {b_}]')
    print(f'Погрешность ε = {eps:.0e}')
    print(f'y({x_0}) = {y_0}')

    step = find_step()
    print("Шаг итерирования: ", round(step, 5))

    X = np.arange(a_, b_ + step, step)
    adams_points = []
    exact_point = exact_points(step, X)

    # Adams
    y = y_0
    adams_points.append(y)
    adams_points.append(exact_point[1])
    for i in range(1, len(X) - 1, 1):
        y = adams(X[i], adams_points[i], X[i - 1], adams_points[i - 1], step)
        adams_points.append(y)

    print()
    print(f"Значения функции в точках методом Адамса:\t{to_fixed(adams_points, 4)}")
    print()
    print(f"Точные значения функции:\t\t\t\t\t{to_fixed(exact_point, 4)}")
    show(to_fixed(adams_points, 4), to_fixed(exact_point, 4))

    # plots
    pylab.cla()
    pylab.plot(X, exact_point, label="точное решение", color=(0, 1, 0))
    pylab.plot(X, adams_points, label="кривая методом Адамса", color=(1, 0, 0))
    pylab.grid(True)
    pylab.legend()
    pylab.savefig("lab10.png")
    pylab.show()