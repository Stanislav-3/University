from scipy.integrate import odeint
import numpy as np
from matplotlib import pylab

m = 1.0
a = 1.3

a_ = 0
b_ = 1
x_0 = 0
y_0 = 0
eps = 0.001


def dy(x, y):
    return a * (1 - y**2) / ((1 + m) * x**2 + y**2 + 1)


def to_fixed(value, digits=0):
    if isinstance(value, list):
        return [to_fixed(i, digits) for i in value]

    return f'{value:.{digits}f}'


def exact(x):
    f = lambda y, x: a * (1 - y**2) / ((1 + m) * x**2 + y**2 + 1)
    sol = odeint(f, y_0, [a_, x])
    return sol[1][0]


def find_step():
    h = eps**0.25
    n = int((b_ - a_) // h)

    if n % 2 != 0:
        n += 1

    while check_step(n):
        n = n // 4 * 2

    while not check_step(n):
        n += 2

    return (b_ - a_) / n


def check_step(n):
    h = (b_ - a_) / n

    y2_1 = Runge_Kutta_(a_ + 2 * h, h)
    y2_2 = Runge_Kutta_(a_ + 2 * h, h * 2)
    delta = (1 / 15) * abs(y2_1 - y2_2)

    return delta < eps


def Runge_Kutta_(x, h):
    if x <= a_:
        return y_0

    prev_x = x - h
    prev_y = Runge_Kutta_(prev_x, h)

    k1 = dy(prev_x, prev_y)
    K2 = dy(prev_x + 0.5 * h, prev_y + 0.5 * h * k1)
    k3 = dy(prev_x + 0.5 * h, prev_y + 0.5 * h * K2)
    k4 = dy(x, prev_y + h * k3)

    return prev_y + h * (k1 + 2 * (K2 + k3) + k4) / 6


def Runge_Kutta(x, y, h):
    h_2 = h / 2

    K1 = dy(x, y)
    K2 = dy(x + h_2, y + h_2 * K1)
    K3 = dy(x + h_2, y + h_2 * K2)
    K4 = dy(x + h, y + h * K3)

    return y + (h / 6) * (K1 + 2 * (K2 + K3) + K4)


def Euler(xs, step, improve=True):
    ys = []
    y = y_0
    for x in xs:
        ys.append(y)
        y = next_y(x, y, step, improve)
    return ys


def next_y(x, y, h, improve=True):
    if improve:
        delta_y = h * dy(x + h / 2, y + h / 2 * dy(x, y))
    else:
        delta_y = h * dy(x, y)

    return y + delta_y


if __name__ == '__main__':
    print(f'Исходные данные: {a:.1f}(1 - y²) / ({1 + m:.1f}x² + y² + 1))')
    print(f'Интервал [{a_}, {b_}]')
    print(f'Погрешность ε = {eps:.0e}')
    print(f'y({x_0}) = {y_0}')

    exact_points = []
    euler_points_g = []
    euler_points_b = []
    runge_kutta_points = []

    step = find_step()
    X = np.arange(a_, b_ + step, step)

    # exact points
    x = a_
    while x <= b_:
        r2 = exact(x)
        exact_points.append(r2)
        x += step
    # Euler points
    euler_points_g = Euler(X, step, True)
    euler_points_b = Euler(X, step, False)

    # Runge-Kutta points
    y = y_0
    for x in X:
        runge_kutta_points.append(y)
        y = Runge_Kutta(x, y, step)


    print()
    print(f"Значения функции в точках (метод Эйлера):\t\t\t {to_fixed(euler_points_b, 4)}")
    print(f"Значения функции в точках (улучшенный метод Эйлера): {to_fixed(euler_points_g, 4)}")
    print(f"Значения функции в точках (метод Рунге-Кутта):\t\t {to_fixed(runge_kutta_points, 4)}")
    print('Точное решение:\t\t\t\t\t\t\t\t\t\t', to_fixed(exact_points, 4))

    pylab.cla()
    pylab.plot(X, exact_points, label="Точное решение", color=(0, 0, 0))
    pylab.plot(X, euler_points_b, label="Метод Эйлера", color=(1, 0, 0))
    pylab.plot(X, euler_points_g, label="улучшенный метод Эйлера", color=(0, 1, 0))
    pylab.plot(X, runge_kutta_points, label="Методом Рунге-Кутта ", color=(0, 0, 1))
    pylab.grid(True)
    pylab.legend()
    pylab.savefig("lab9.png")
    pylab.show()
