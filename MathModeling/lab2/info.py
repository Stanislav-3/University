import numpy as np
import random


N = int(10 ** 3 / 2)


def f(x, k, _lambda):
    if x < 0:
        return 0
    else:
        return (k / _lambda) * (x / _lambda) ** (k - 1) * np.exp(-(x / _lambda) ** k)


# def F(x, k, _lambda):
#     return 1 - np.exp(-(_lambda * x) ** k)


def gen1(p: float) -> bool:
    return True if random.random() < p else False


def gen4(p: list):
    # assert sum(p) == 1

    value = random.random()
    s = 0.
    for i, p_i in enumerate(p):
        s += p_i
        if s > value:
            return i

    return len(p) - 1


