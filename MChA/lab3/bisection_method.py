import func
import math

def bisection_method(f, a, b, eps):
    x = (a + b) / 2
    k = 0
    while math.fabs(func.substitute(f, x)) >= eps:
        k += 1
        x = (a + b) / 2
        a, b = (a, x) if func.substitute(f, a) * func.substitute(f, x) < 0 else (x, b)
    return (a + b) / 2, k