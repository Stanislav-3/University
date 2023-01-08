import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from scipy.integrate import quad
from info import f, N, gen4
import scipy


def find_bounds(k=1.5, _lambda=0.5, eps=10*-6):
    l, r = 0, None
    w = scipy.stats.weibull_min.ppf(c=k, scale=_lambda, q=1-eps)
    r = w
    return l, r


def get_intervals_with_p(bins, k, _lambda, eps):
    l, r = find_bounds(k, _lambda, eps)

    delta = (r - l) / bins

    r_points = []

    for i in range(1, bins + 1):
        r_points.append(l + i * delta)

    probabilities = [quad(f, l, r, args=(k, _lambda))[0] for l, r in zip([l] + r_points[:-1], r_points)]

    return [l] + r_points, probabilities


def get_plot_data2(k, _lambda, eps=10**-3):
    intervals, probabilities = get_intervals_with_p(bins=300, k=k, _lambda=_lambda, eps=eps)

    # bins = [0.] * len(probabilities)
    points = []
    for i in range(N):
        segment = gen4(probabilities)
        points.append(intervals[segment + 1])

    ls = np.linspace(intervals[0], intervals[-1], 50)

    return {
        'empirical': (
            points
        ),
        'analytical': (
            ls,
            [f(y, k=k, _lambda=_lambda) for y in ls]
        )}


def plot(k=1.5, _lambda=0.5, eps=10*-2):
    plot_data = get_plot_data2(k, _lambda, eps)
    plt.hist(plot_data['x'], bins=25, density=True, label="Generated", color="red")
    plt.plot(*plot_data['analytical'], label="Analytical", color="blue")

    plt.show()