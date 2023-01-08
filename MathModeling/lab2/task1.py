import random
import numpy as np
from scipy.special import logsumexp
from info import N
from parser import get_inverse_function, get_parameter_names


# def F_inv(y, k, _lambda):
#     return (logsumexp(-np.log(1 - y)) ** (1 / k)) * _lambda

F_inv = None


def set_F_get_params(s):
    global F_inv

    F_inv = get_inverse_function(s)

    return get_parameter_names()


def get_Y(*args):
    x = random.random()
    return F_inv(x, *args)


def generate_Y1(*args) -> list:
    _points = []

    for i in range(N):
        _points.append(get_Y(*args))

    _points.sort()
    return _points


def get_plot_data1(*args):
    points = generate_Y1(*args)
    ls = np.linspace(points[0], points[-1], 50)

    return {
        'empirical': points,
        # 'analytical': (
        #     ls,
        #     [f(y, *args) for y in ls]
        # )
    }
