import numpy as np
import matplotlib.pyplot as plt


a, b = 0, 2

# arctg(x)
ddf = lambda x: -(2 / (x + 1) + 1 / x) * 0.5 * df(x)
df = lambda x: 1 / (2 * np.sqrt(x) * (x + 1))
f  = lambda x: np.arctan(np.sqrt(x))
F  = lambda x: (x + 1) * f(x) - np.sqrt(x)


integral = F(b) - F(a)


def find_derivative(eps=0.01):
    delta = np.Inf
    n = 3
    derivative = 0
    while (delta > eps):
        n += 2
        X = np.linspace(a, b, n)
        Y = f(X)
        i = int(len(X) / 2)
        derivative = (Y[i + 1] - Y[i - 1]) / (X[i + 1] - X[i - 1])
        delta = abs(df(0.5 * (a + b)) - derivative)

    return derivative, delta, (b - a) / n


def find_second_derivative(eps=0.01):
    delta = np.Inf
    n = 3
    while (delta > eps):
        n += 2
        X = np.linspace(a, b, n)
        Y = f(X)
        i = int(len(X) / 2)
        second_derivative = (Y[i + 1] + Y[i - 1] - 2 * Y[i]) / (X[i] - X[i - 1]) ** 2
        delta = abs(ddf(0.5 * (a + b)) - second_derivative)

    return second_derivative, delta, (b - a) / n


def calc(integrate, a=0, b=2, eps=1e-6, option=None):
    delta = np.Inf
    s = 0
    n = int(1 / eps)
    while delta > eps:
        X = np.linspace(a, b, n)
        Y = f(X)

        if option == 'simpson':
            s = integrate(n=n)
        elif option is not None:
            s = integrate(X, Y, option=option)
        else:
            s = integrate(X, Y)

        delta = abs(s - integral)
        n += 50

    return s, delta, (b - a) / n


def my_rectangles(X, Y, option='left'):
    s = 0
    if option == 'left':
        for i in range(len(X) - 1):
            s += (X[i + 1] - X[i]) * Y[i]

    elif option == 'right':
        for i in range(len(X) - 1):
            s += (X[i + 1] - X[i]) * Y[i + 1]

    elif option == 'middle':
        for i in range(len(X) - 1):
            h = (X[i + 1] - X[i])
            s += h * f(X[i] + h / 2)

    return s


def my_trapeze(X, Y):
    s = 0
    for i in range(len(X) - 1):
        s += (X[i + 1] - X[i]) * (Y[i] + Y[i + 1]) / 2

    return s


def my_simpson(a=0, b=2, n=0):
    h = (b - a) / n
    k = 0.0
    x = a + h
    for i in range(1, n // 2 + 1):
        k += 4 * f(x)
        x += 2 * h

    x = a + 2 * h
    for i in range(1, n // 2):
        k += 2 * f(x)
        x += 2 * h

    return (h / 3) * (f(a) + f(b) + k)


if __name__ == '__main__':
    print(25 * '*' + ' Вычисление производных ' + 25 * '*')
    first_derivative = find_derivative()
    print('Точное значение первой производной:\t\t\t\t\t f\'(x) =', df(0.5 * (a + b)))
    print()

    print(f'Найденное значение первой производной:\t\t\t\t f\'(x) = {first_derivative[0]:.3f}')
    print(f'Погрешность:\t\t\t\t\t\t\t\t\t\t ε = {first_derivative[1]:.3f}')
    print(f'Отрезок:\t\t\t\t\t\t\t\t\t\t\t Δh = {first_derivative[2]:.3f}')
    print()

    second_derivative = find_second_derivative()
    print('Точное значение второй производной:\t\t\t\t\t f\'\'(x) =', ddf(0.5 * (a + b)))
    print(f'Найденное значение второй производной:\t\t\t\t f\'\'(x) = {second_derivative[0]:.3f}')
    print(f'Погрешность:\t\t\t\t\t\t\t\t\t\t ε = {second_derivative[1]:.3f}')
    print(f'Отрезок:\t\t\t\t\t\t\t\t\t\t\t Δh = {second_derivative[2]:.3f}')
    print(74 * '-')
    print()

    print(26 * '*' + ' Вычисление интегралов ' + 25 * '*')
    print('Точное значание интеграла:\t\t\t\t\t\t\t', integral)
    print()

    eps_text = '10⁻⁶'
    left_rec = calc(my_rectangles, option='left')
    print('Значение интеграла (метод левых прямоугольников):\t', left_rec[0])
    print(f'Точность значения:\t\t\t\t\t\t\t\t\t ε = {left_rec[1]:.3e} < {eps_text}')
    print(f'Для данной точности требуется шаг:\t\t\t\t\t Δh = {left_rec[2]:.3e}')
    print()

    mid_rec = calc(my_rectangles, option='middle')
    print('Значение интеграла (метод средних прямоугольников):\t', mid_rec[0])
    print(f'Точность значения:\t\t\t\t\t\t\t\t\t ε = {mid_rec[1]:.3e} < {eps_text}')
    print(f'Для данной точности требуется шаг:\t\t\t\t\t Δh = {mid_rec[2]:.3e}')
    print()

    right_rec = calc(my_rectangles, option='right')
    print('Значение интеграла (метод праых прямоугольников):\t', right_rec[0])
    print(f'Точность значения:\t\t\t\t\t\t\t\t\t ε = {right_rec[1]:.3e} < {eps_text}')
    print(f'Для данной точности требуется шаг:\t\t\t\t\t Δh = {right_rec[2]:.3e}')
    print()

    trapeze = calc(my_trapeze)
    print('Значение интеграла (метод трапеций):\t\t\t\t', trapeze[0])
    print(f'Точность значения:\t\t\t\t\t\t\t\t\t ε = {trapeze[1]:.3e} < {eps_text}')
    print(f'Для данной точности требуется шаг:\t\t\t\t\t Δh = {trapeze[2]:.3e}')
    print()

    simpson = calc(my_simpson, option='simpson')
    print('Значение интеграла (метод Симпсона):\t\t\t\t', simpson[0])
    print(f'Точность значения:\t\t\t\t\t\t\t\t\t ε = {simpson[1]:.3e} < {eps_text}')
    print(f'Для данной точности требуется шаг:\t\t\t\t\t Δh = {simpson[2]:.3e}')
    print(74 * '-')
