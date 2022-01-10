import random
import math
import matplotlib.pyplot as plt
from scipy import stats
import numpy as np
import enum


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


def find_M_y(y_: list):
    return sum(y_) / len(y_)


def find_D_y(y_: list, m=None):
    D = 0
    if m is None or m == {}:
        m = find_M_y(y_)
    elif type(m) == dict:
        m = m.get('m')

    for y_i in y_:
        D += (y_i - m)**2

    if m is None:
        n = len(y_) - 1
    else:
        n = len(y_)

    return D / n


def get_chi_squared(p, df):
    return stats.chi2.ppf(p, df)


def get_normal(p):
    p += (1 - p) / 2
    return stats.norm.ppf(p)


def find_CI_for_M_y(y_, confidence_level, d=None):
    m = find_M_y(y_)
    if d is None or d == {}:
        d = find_D_y(y_)
    elif type(d) == dict:
        d = d.get('d')
    eps = get_normal(confidence_level) * math.sqrt(d / len(y_))

    return m - eps, m + eps


def find_CI_for_D_y(y_, confidence_level, m=None):
    d = find_D_y(y_, m)
    n = len(y_)
    if m is None:
        l = (n - 1) * d / get_chi_squared((1 + confidence_level) / 2, n - 1)
        r = (n - 1) * d / get_chi_squared((1 - confidence_level) / 2, n - 1)
    else:
        l = n * d / get_chi_squared((1 + confidence_level) / 2, n)
        r = n * d / get_chi_squared((1 - confidence_level) / 2, n)
    return l, r


def get_delta(x1, x2, l=5, get_number=False):
    if get_number == True:
        return abs(x1 - x2)
    else:
        return f'{abs(x1 - x2):.{l}f}'


def check_CI(interval: tuple, Q):
    if Q > interval[0] and Q < interval[1]:
        return 'yes'
    else:
        return 'no'


class DependencyMode(enum.Enum):
    CI_SIZE__SAMPLE_SIZE = 0,
    CI_SIZE__SIGNIFICANCE_LEVEL = 1


def my_plot(mode: DependencyMode):
    def plot_CI_Size_dependence_from_Sample_Size(tittle:str, func, **kwargs, ):
        plt.title(tittle)
        # plt.xlabel('Sample size')
        # plt.ylabel('CI size')
        X = [num for num in range(30, 1000)]
        significance_level = 0.90
        Y = []
        for size in X:
            m = 0
            for i in range(75):
                y_ = generate_y(size)
                interval = func(y_, significance_level, kwargs)
                m += get_delta(*interval, get_number=True)
            Y.append(m / 75)
            # interval = func(y_, significance_level, kwargs)
            # Y.append(get_delta(*interval, get_number=True))
        plt.plot(X, Y)

    def plot_CI_Size_dependence_from_apha(tittle:str, func, **kwargs):
        plt.title(tittle)
        # plt.xlabel('Alpha')
        # plt.ylabel('CI size')
        size = 100
        y_ = generate_y(size)

        X = np.linspace(0.01, 0.999, 1000)
        Y = []
        for significance_level in X:
            interval = func(y_, significance_level, kwargs)
            Y.append(get_delta(*interval, get_number=True))
        plt.plot(X, Y)

    if mode == DependencyMode.CI_SIZE__SAMPLE_SIZE:
        plot_func = plot_CI_Size_dependence_from_Sample_Size
        plt.suptitle('Зависимость величины доверительного интервала от объема выборки')
    elif mode == DependencyMode.CI_SIZE__SIGNIFICANCE_LEVEL:
        plot_func = plot_CI_Size_dependence_from_apha
        plt.suptitle('Зависимость величины доверительного интервала от 1 - α')

    plt.axes(plt.subplot(221))
    plot_func('CI for M[y]', find_CI_for_M_y)
    plt.axes(plt.subplot(223))
    plot_func('', find_CI_for_M_y, d=D_y)
    plt.axes(plt.subplot(222))
    plot_func('CI for D[y]', find_CI_for_D_y)
    plt.axes(plt.subplot(224))
    plot_func('', find_CI_for_D_y, m=M_y)
    plt.show()


if __name__ == '__main__':
    a, b = 0, 1
    M_y = 2 / math.pi * math.log(2)
    D_y = 4 / math.pi - 1 - M_y ** 2
    print(f'M[y]  = {M_y:.6f}')
    print(f'D[y]  = {D_y:.6f}')
    print()

    y = generate_y(30)
    m_y = find_M_y(y)
    d_y = find_D_y(y)
    d_y_with_M_y = find_D_y(y, m=M_y)
    print(f'Sample size = {len(y)}')
    print(f'M ⃰[y] = {m_y:.6f} | Δ = {get_delta(M_y, m_y)}')
    print(f'D ⃰[y] = {d_y:.6f} | Δ = {get_delta(D_y, d_y)}')
    print(f'D ⃰[y] = {d_y_with_M_y:.6f} | Δ = {get_delta(D_y, d_y_with_M_y)} | (with analytical M[y])')
    print()

    confedence_level = 0.90
    CI_for_m_y = find_CI_for_M_y(y, confedence_level)
    CI_for_m_y_with_D_y = find_CI_for_M_y(y, confedence_level, d=D_y)
    CI_for_d_y = find_CI_for_D_y(y, confedence_level)
    CI_for_d_y_with_M_y = find_CI_for_D_y(y, confedence_level, m=M_y)
    print(f'CI for M[y] = [{CI_for_m_y[0]:.6f}, {CI_for_m_y[1]:.6f}] | 1 - α = {confedence_level} '
          f'| In? -{check_CI(CI_for_m_y, M_y)}')
    print(f'CI for M[y] = [{CI_for_m_y_with_D_y[0]:.6f}, {CI_for_m_y_with_D_y[1]:.6f}] '
          f'| 1 - α = {confedence_level} | In? -{check_CI(CI_for_m_y_with_D_y, M_y)} | (with analytical D[y])')

    print(f'CI for D[y] = [{CI_for_d_y[0]:.6f}, {CI_for_d_y[1]:.6f}] | 1 - α = {confedence_level} '
          f'| In? -{check_CI(CI_for_d_y, D_y)}')
    print(f'CI for D[y] = [{CI_for_d_y_with_M_y[0]:.6f}, {CI_for_d_y_with_M_y[1]:.6f}] '
          f'| 1 - α = {confedence_level} | In? -{check_CI(CI_for_d_y_with_M_y, D_y)} | (with analytical M[y])')
    print()

    my_plot(DependencyMode.CI_SIZE__SAMPLE_SIZE)
    my_plot(DependencyMode.CI_SIZE__SIGNIFICANCE_LEVEL)