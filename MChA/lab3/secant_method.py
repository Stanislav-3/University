import func

def secant_method(f, a, b, eps):
    f1 = func.derivative(f)
    f2 = func.derivative(f1)
    x_n_prev = None
    stat = None
    ans_a = func.substitute(f, a) * func.substitute(f2, a)
    ans_b = func.substitute(f, b) * func.substitute(f2, b)

    if ans_a > 0:
        x_n_prev = a
        stat = b
    elif ans_b > 0:
        x_n_prev = b
        stat = a

    f_stat = func.substitute(f, stat)
    k = 0
    while (True):
        k += 1
        f_n_prev = func.substitute(f, x_n_prev)
        x_n_new = x_n_prev - ((stat - x_n_prev) / (f_stat - f_n_prev)) * (f_n_prev)

        if (abs(x_n_prev - x_n_new) < eps):
            return x_n_new, k

        x_n_prev = x_n_new