from scipy.stats import weibull_min
import numpy as np
import scipy


def get_E(X: list):
    return sum(X) / len(X)


def get_Std(X: list):
    centered = (np.array(X) - get_E(X))
    S2 = (centered @ centered) / (len(X) - 1)
    return S2 ** (1 / 2)


def get_analytical_moments(*args):
    k, _lambda = args
    w = weibull_min.rvs(k, size=10**6, scale=_lambda)
    return w.mean(), w.std()


def get_theoretical_moments(f, *args):
    Mx = scipy.integrate.quad(lambda x : x * f(x, *args), -np.inf, np.inf)[0]
    Dx = scipy.integrate.quad(lambda x : (x - Mx)**2 * f(x, *args), -np.inf, np.inf)[0]

    return Mx, Dx


def get_empirical_moments(points):
    return get_E(points), get_Std(points)