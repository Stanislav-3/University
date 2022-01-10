import numpy as np
import matplotlib.pyplot as plot

a, b = -3, 3
dots_count = 10

def f(x):
    return np.sinh(x)
    # return (np.cos(x) ** 9 * np.sin(x) ** 9 * np.tanh(x) ** 9)
def get_dots():
    dots = []
    for i in range(dots_count):
        x = a + (b - a) * i / (dots_count - 1)
        y = f(x)
        dots += [(x, y)]

    return dots

def tridiag_solve(A, b):
    A = A.copy()
    b = b.copy()

    A[0][1] /= A[0][0]
    for i in range(1, len(A) - 1):
        A[i][i + 1] /= (A[i][i] - A[i][i - 1] * A[i - 1][i])

    b[0] /= A[0][0]
    for i in range(1, len(A)):
        b[i] = (b[i] - A[i][i - 1] * b[i - 1]) / (A[i][i] - A[i][i - 1] * A[i - 1][i])

    x = np.zeros(len(A))
    x[-1] = b[-1]
    for i in range(len(A) - 2, -1, -1):
        x[i] = b[i] - A[i][i + 1] * x[i + 1]

    return x


def Spline(dots):
    n = len(dots) - 1
    (x, y) = map(list, zip(*dots))

    h = [None]
    for i in range(1, n + 1):
        h += [x[i] - x[i - 1]]

    A = [[None] * (n) for i in range(n)]
    for i in range(1, n):
        for j in range(1, n):
            A[i][j] = 0.0

    for i in range(1, n - 1):
        A[i + 1][i] = h[i + 1]

    for i in range(1, n):
        A[i][i] = 2 * (h[i] + h[i + 1])

    for i in range(1, n - 1):
        A[i][i + 1] = h[i + 1]

    F = []
    for i in range(1, n):
        F += [3 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i])]

    A = [A[i][1:] for i in range(len(A)) if i]

    c = tridiag_solve(A, F)
    c = [0.0] + list(c) + [0.0]

    def evaluate(xdot):
        for i in range(1, len(x)):
            if x[i - 1] <= xdot <= x[i]:
                val = 0
                val += y[i]
                b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
                val += b * (xdot - x[i])
                val += c[i] * ((xdot - x[i]) ** 2)
                d = (c[i] - c[i - 1]) / (3 * h[i])
                val += d * ((xdot - x[i]) ** 3)
                return val
        return None

    return evaluate

def my_plot(x, y, kind):
    ls = np.linspace(min(x), max(x), 10000)
    plot.plot(x, y, 'ko', color='red')

    if kind == "arctg":
        plot.plot(ls, f(ls), 'blue')
        plot.suptitle("arctg(x)")
    elif kind == "spline":
        spline = Spline(dots)
        y = [spline(xdot) for xdot in ls]
        plot.plot(ls, y, 'darkgreen')
        plot.suptitle("Spline")
    else:
        plot.plot(ls, f(ls), 'blue')
        spline = Spline(dots)
        y_ls = [spline(xdot) for xdot in ls]
        plot.plot(ls, y_ls, 'darkgreen')
        plot.suptitle("arctg(x) and spline")

    plot.grid()
    plot.show()

if __name__ == '__main__':
    dots = get_dots()
    (x, y) = map(list, zip(*dots))
    print("Dots:")
    print("(x,y) = ", *dots[:3], '\n', *dots[3:], end='\n\n')

    spline = Spline(dots)
    x_dot = 0.5 * (b - a)
    print(f"f({x_dot})\t\t\t\t=", f(x_dot))
    print(f"cubic_spline({x_dot})\t=", spline(x_dot))
    print(f"delta({x_dot})\t\t\t=", abs(f(x_dot) - spline(x_dot)))

    my_plot(x, y, "arctg")
    my_plot(x, y, "spline")
    my_plot(x, y, "all")