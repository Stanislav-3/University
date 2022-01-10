# import matplotlib
# import matplotlib.pyplot as plt
# from matplotlib.widgets import Slider, Button
# matplotlib.use('Qt5Agg')

import numpy as np
import random
import math


def get_y():
    def get_x():
        a_, b_ = 0, math.pi / 4
        return a_ + random.random() * (b_ - a_)

    def Y_f(x):
        return math.tan(x)

    return Y_f(get_x())


def generate_y(n_: int):
    y_ = []

    for i in range(n_):
        y_.append(get_y())

    y_.sort()
    return y_


def f(y_):
    if y_ < a or y_ > b:
        return 0
    else:
        return 4 / (math.pi * (1 + y_**2))


def F(y_):
    if y_ < a:
        return 0
    elif y_ > b:
        return 1
    else:
        return 4 / math.pi * math.atan(y_)


def get_empirical_F(y_: list):
    X, Y = [], []
    p = 1 / len(y_)

    i = 0
    while i < len(y_):
        X.append(y_[i])
        i += 1
        Y.append(p * i)

    return X, Y


def get_data_for_equiprobable_method(y_: list, g_: int, ) -> list:
    left_bound_and_height = [[a, None]]

    obligatory = len(y_) // g_
    additional = len(y_) % g_

    S = 0
    L = 0
    i, interval = 0, 0
    while interval < g_:
        if additional:
            additional -= 1
            amount = obligatory + 1
        else:
            amount = obligatory

        i += amount

        if interval == g_ - 1 or i > len(y_) - 1:
            r = b
        else:
            r = (y_[i] + y_[i - 1]) / 2
            left_bound_and_height.append([r, None])

        dx = r - left_bound_and_height[interval][0]

        h = amount
        left_bound_and_height[interval][1] = h
        S += h * dx
        L += h
        if r == b:
            break
        interval += 1

    for lh in left_bound_and_height:
        lh[1] /= len(y_)

    return left_bound_and_height


def add_output(func):
    def wrapped(*args):
        res = f'{func.__name__}: {func(*args)}'

        if func.__name__ == 'Pierson':
            res += f' | число степеней свободы = {args[1] - 2}'
        elif func.__name__ == 'Mises':
            res += ' | '
        elif func.__name__ == 'Kolmogorov':
            res += ' | '

        return res

    return wrapped


@add_output
def Kolmogorov(n_: int):
    y = generate_y(n_)

    # analytical = [F(y) for y in y]
    empirical = get_empirical_F(y)[1]

    # res = np.abs(np.array(analytical) - np.array(empirical))

    res = []
    for i in range(len(y) - 1):
        delta1 = abs(F(y[i]) - empirical[i])
        delta2 = abs(F(y[i]) - empirical[i + 1])
        res.append(max(delta1, delta2))
    res.append(abs(F(y[len(y) - 1]) - empirical[len(y) - 1]))

    return max(res) * math.sqrt(n_)


@add_output
def Mises(n_: int):
    y = generate_y(n_)
    analytical = [F(y) for y in y]

    delta = 1 / (12 * n_)

    for i, y_ in enumerate(y):
        delta += (analytical[i] - (i + 0.5) / n_) ** 2

    return delta


@add_output
def Pierson(n_: int, g_: int = None):
    y = generate_y(n_)

    if g_ is None:
        if n_ < 100:
            g_ = int(math.sqrt(n_))
        else:
            g_ = int(2 * 3 * 4 * math.log(n_))

    left_bound_and_height = get_data_for_equiprobable_method(y, g_)
    empirical_p = [lh[1] for lh in left_bound_and_height]

    left_bound_and_height.append([b, None])
    analytical_p = [F(left_bound_and_height[i + 1][0]) - F(left_bound_and_height[i][0]) for i in range(g_)]
    assert abs(1 - sum(analytical_p)) <= 0.01

    res = 0
    for i in range(g_):
        res += (empirical_p[i] - analytical_p[i]) ** 2 / analytical_p[i]
    res *= n_

    return res


if __name__ == '__main__':
    a, b = 0, 1
    print(Kolmogorov(30))
    print(Mises(50))
    print(Pierson(200, 10))