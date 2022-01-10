import func

def newton_method(f, a, b, eps):
    f1 = func.derivative(f)
    f2 = func.derivative(f1)
    ans_a = func.substitute(f, a) * func.substitute(f2, a)
    ans_b = func.substitute(f, b) * func.substitute(f2, b)

    x_n_prev = None
    if ans_a > 0:
        x_n_prev = a
        stat = b

    elif ans_b > 0:
        x_n_prev = b
        stat = a
    k = 0
    while (True):
        k += 1
        f_n_prev = func.substitute(f, x_n_prev)
        f_n_prev_diff = func.substitute(f1, x_n_prev)
        x_n_new = x_n_prev - (f_n_prev / f_n_prev_diff)
        f_n_new = func.substitute(f, x_n_new)
        if abs(f_n_new) < eps:
            return x_n_new, k
        x_n_prev = x_n_new