import numpy as np
import scipy
from scipy.stats import weibull_min
from scipy.integrate import quad
from info import f


def find_probabilities(task, points, k, _lambda, bins):
    analytical, empirical = [], []

    if task == '2':
        for number, count in zip(*np.unique(points, return_counts=True)):
            analytical.append(f(number, k, _lambda))
            empirical.append(count / len(points))

    if task == '1':
        hist, edges = np.histogram(points, bins)

        for i in range(len(edges) - 1):
            l, r = edges[i], edges[i + 1]

            p = quad(f, l, r, args=(k, _lambda))[0]
            # p = F(r) - F(l)
            analytical.append(p)

            t = np.where(np.logical_and(points > l, points <= r))
            count = len(*t)
            if i == 0:
                count += 1

            empirical.append(count / len(points))

    return analytical, empirical


def get_chi2_and_pValue(task, points, k=1.5, _lambda=0.5, bins=2):
    analytical, empirical = find_probabilities(task, points, k, _lambda, bins)

    chi2 = 0.
    for i in range(len(analytical)):
        chi2 += (empirical[i] - analytical[i]) ** 2 / analytical[i]

    p_value = scipy.stats.distributions.chi2.sf(chi2, len(points) - 1)

    return chi2, p_value
