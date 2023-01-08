import numpy as np
import time
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('Qt5Agg')


A = time.time()


def rand(m=2**20, k=5**8):
    global A
    A = (k * A) % m

    return A / m


if __name__ == "__main__":
    t0 = time.time()

    x = [rand() for _ in range(10**6)]

    frequency, bins = np.histogram(x, bins=10**2, density=True)
    plt.hist(bins[:-1], bins=bins, weights=frequency)

    print(f'Time: {time.time() - t0}')
    plt.gca().set(title='Frequency Histogram', ylabel='Frequency')
    plt.show()
