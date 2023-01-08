from scipy.optimize import minimize
import time
import numpy as np
import collections
import math


import re

f = None
arguments = []


def _func_builder(arg_names, return_expr):
    def func(x, *args):
        x = float(x)

        if type(x) is not float:
            print(type(x))
            exit(10)

        for arg_name, arg in zip(arg_names, args):
            exec(f'{arg_name} = {arg}')

        return eval(return_expr)

    return func


def _alter(s, element, element2):
    start = 0

    while True:
        idx = s.find(element, start)
        start = idx + len(element) + len(element2)

        if idx != -1:
            s = s[:idx] + element2 + s[idx + len(element):]
        else:
            break

    return s


def func_parser(s: str):
    global arguments

    expressions = re.findall(r'[a-z]+', s)

    if 'x' not in expressions:
        raise ValueError('Expression\'s got no x')

    while 'x' in expressions:
        expressions.remove('x')

    for expression in set(expressions):
        is_variable = True

        if expression in {'pi', 'e', 'exp'}:
            s = _alter(s, expression, 'np.' + expression)
            is_variable = False

        if expression == 'log':
            s = _alter(s, expression, 'math.log')
            is_variable = False

        if expression == 'ln':
            is_variable = False

        if is_variable:
            arguments.append(expression)

    if len(arguments) > 2:
        raise ValueError('Too much parameters, only [0, 2] instead of x is possible')
    arguments.sort()

    s = _alter(s, 'ln', 'np.log')
    s = _alter(s, '^', '**')

    print('parsed func: ', s)

    return _func_builder(arguments, s)


def _objective(x, y, *args):
    global f
    return abs(f(x, *args) - y)


def f_inv(y, *args, **kwargs):
    # ordered_kwargs = collections.OrderedDict(sorted(kwargs.items()))
    # args = list(ordered_kwargs.values())
    args = [y] + list(args)
    res = minimize(_objective, np.array(1), args=tuple(args), method='Nelder-Mead', tol=1e-4)

    if res['message'] != 'Optimization terminated successfully.':
        raise RuntimeError(f'Optimizer stopped with an message: {res["message"]}')

    return res['x'][0]


def get_inverse_function(s):
    global f
    f = func_parser(s)

    return f_inv


def get_parameter_names():
    return arguments

