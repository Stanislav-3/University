def get_border(f, l: int, r: int):
    borders = []
    borders.append(l)
    flag_positive = False
    flag_negative = False
    for i in range(l, r):

        s = substitute(f, i)
        if s < 0:
            flag_negative = True
            if flag_positive:
                borders.append(i)
            flag_positive = False
        else:
            flag_positive = True
            if flag_negative:
                borders.append(i)
            flag_negative = False
    borders.append(r)
    k = 0
    n = len(borders) - 2
    for j in range(0, n, 1):
        print(borders[j:j + 2], end=", ")
    print(borders[n:n + 2])
    return borders

def substitute(storage, x):
    res = 0
    for i in range(len(storage) - 1, -1, -1):
        res += storage[abs(i - (len(storage) - 1))] * x ** i
    return res


def w(data, x):
    flag_positive = False
    flag_negative = False
    count_changed = 0
    for l in data:

        ans = substitute(l, x)
        if ans < 0:
            flag_negative = True
            if flag_positive:
                count_changed += 1
            flag_positive = False
        else:
            flag_positive = True
            if flag_negative:
                count_changed += 1
            flag_negative = False
    return count_changed


def derivative(poly):
    res = []
    for i in range(len(poly) - 1):
        res.append(poly[i] * abs(i - (len(poly) - 1)))
    return res

def negate(poly):
    for i in range(len(poly)):
        poly[i] = -1 * poly[i]
    return poly

def sturm_subs(seq, x):
    ans = []
    for i in range(len(seq)):
        res = 0
        for j in range(len(seq[i])):
            res = res * x + seq[i][j]
        ans.append(res)
    return ans

def isZero(poly):
    if poly[0] >= 0.0000001:
        return False
    else:
        return True