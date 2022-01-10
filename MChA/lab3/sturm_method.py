import func
import numpy as np

def count_roots(p, l, r):
    sturms_seq = [p, func.derivative(p)]
    f = func.negate(np.polydiv(sturms_seq[-2], sturms_seq[-1])[1].tolist())
    while not func.isZero(f):
        sturms_seq.append(f)
        f = func.negate(np.polydiv(sturms_seq[-2], sturms_seq[-1])[1].tolist())

    sturms_seq_at_l = func.sturm_subs(sturms_seq, l)
    sturms_seq_at_r = func.sturm_subs(sturms_seq, r)

    nl = 0
    for i in range(len(sturms_seq_at_l) - 1):
        if sturms_seq_at_l[i] * sturms_seq_at_l[i + 1] < 0:
            nl += 1

    nr = 0
    for i in range(len(sturms_seq_at_r) - 1):
        if sturms_seq_at_r[i] * sturms_seq_at_r[i + 1] < 0:
            nr += 1

    return nl - nr
