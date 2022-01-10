# basic operations
def bsum(a, b, rus_output=False):
    bigger_len = len(a) if len(a) > len(b) else len(b)
    a = expand_to_len(a, bigger_len)
    b = expand_to_len(b, bigger_len)

    if rus_output:
        print(('Считаем сумму следующих чисел в прямом коде:\n'
              '{0}(2) = {1}(10)\n'
              '{2}(2) = {3}(10)\n'
              ).format(a, binstring_to_int(a),
                       b, binstring_to_int(b)))
        print('| A | B | (e) | -> | S | (e) |\n' + '-'*34)
    c = ''
    extra_bit = False
    for a_bit, b_bit in zip(reversed(a), reversed(b)):
        old_extra_bit = extra_bit

        if bool(b_bit == '1') != extra_bit:
            if a_bit == '0':
                c = '1' + c
                extra_bit = False
            else:
                c = '0' + c
                extra_bit = True
        else:
            c = a_bit + c
        if rus_output:
            print(('| {0} | {1} | ({2}) | -> | {3} | ({4}) |'
                  ).format(a_bit, b_bit,
                           '1' if old_extra_bit else '0',
                           c[0],
                           '1' if extra_bit else '0'))

    if rus_output:
        print(('\nРезультат суммы в прямом коде:\n'
               'a + b = c\n'
               'a = {0}(2) = {1}(10)\n'
               'b = {2}(2) = {3}(10)\n'
               'c = {4}(2) = {5}(10)\n'
               'Переполнение для прямого кода '
               + ('есть' if extra_bit else 'отсутствует') + '.'
              ).format(a, binstring_to_int(a),
                       b, binstring_to_int(b),
                       c, binstring_to_int(c)))

    return c, extra_bit


def oc_sum(a, b):
    s = sum(a, b)
    if s[1]:
        return sum(s[0], '01')[0]
    else:
        return s[0]


def oc_dif(a, b):
    b = invert_bits(b)
    s = sum(a, b)
    if s[1]:
        return sum(s[0], '01')[0]
    else:
        return invert_bits(s[0])


def invert_bits(a):
    b = ''
    for c in a:
        b += '1' if c == '0' else '0'

    return b


def neg(a):
    b = invert_bits(a)
    d = bsum(b, '01')[0]

    if a == d:
        return d, True
    else:
        return d, False


def expand_to_len(a, new_len):
    assert new_len >= len(a)
    return a[0]*(new_len-len(a)) + a


def shift_left(a, shift = 1):
    for _ in range(shift):
        a = a[1:] + '0'

    return a


def logical_shift_right(a, shift = 1):
    for _ in range(shift):
        a = '0' + a[:-1]

    return a


def arithmetic_shift_right(a, shift = 1):
    for _ in range(shift):
        a = a[0] + a[:-1]

    return a


# arithmetic
def _align(a, b):
    if len(a) < len(b):
        a = expand_to_len(a, len(b))
    elif len(a) > len(b):
        b = expand_to_len(b, len(a))

    return a, b


def sum(a, b, rus_output=False):
    bigger_len = len(a) if len(a) > len(b) else len(b)
    a = expand_to_len(a, bigger_len)
    b = expand_to_len(b, bigger_len)

    if rus_output:
        print(('Считаем сумму следующих чисел в дополнительном коде:\n'
               '{0}(2) = {1}(10)\n'
               '{2}(2) = {3}(10)\n'
               ).format(a, twos_comp_binary_string_to_int(a),
                        b, twos_comp_binary_string_to_int(b)))
        print('Она соответствует сумме в прямом коде, поэтому...\n')

    a_sign = a[0]
    b_sign = b[0]

    error_bool = False
    c = bsum(a, b, rus_output)[0]
    if a_sign == b_sign and c[0] != a_sign:
        error_bool = True

    if rus_output:
        print(('\n'
               'Результат суммы в дополнительном коде:\n'
               'a + b = c\n'
               'a = {0}(2) = {1}(10)\n'
               'b = {2}(2) = {3}(10)\n'
               'c = {4}(2) = {5}(10)\n'
               'Переполнение для дополнительного кода '
               + ('есть' if error_bool else 'отсутствует') + '.'
              ).format(a, twos_comp_binary_string_to_int(a),
                       b, twos_comp_binary_string_to_int(b),
                       c, twos_comp_binary_string_to_int(c)))

    return c, error_bool


def dif(a, b, rus_output=False):
    a, b = _align(a, b)
    nb = neg(b)

    if rus_output:
        print(('Считаем разность следующих чисел в дополнительном коде:\n'
               '{0}(2) = {1}(10)\n'
               '{2}(2) = {3}(10)\n'
               ).format(a, twos_comp_binary_string_to_int(a),
                        b, twos_comp_binary_string_to_int(b)))
        print('Она соответствует сумме первого '
              'и отрицания второго, поэтому...')
        print(('Отрицание второго числа:\n{0}, ошибка {1}.\n'
              ).format(nb[0], 'есть' if nb[1] else 'отсутствует'))

    c = bsum(a, nb[0], rus_output)

    if rus_output:
        print('Результат разности соответствует '
              'результату суммы в дополнительном коде.')

    return c

def mul(a, b):
    p = '0'
    a, b = _align(a, b)

    for bit in reversed(a):
        if bit == '1':
            p = sum(p, b)
        b = shift_left(b)

    return p


def full_mul(a, b):
    p = '0'*(len(a)+len(b))
    for bit in reversed(a):
        if bit == '1':
            p = sum(p, b)[0]
        b += '0'

    return p


def imul(m, r, rus_output=False):
    if rus_output:
        print('Перемножим следующие числа в дополнительном коде '
              'по алгоритму Бута:')
        print('m = {0}(2) = {1}(10)'.format(m,
               twos_comp_binary_string_to_int(m)))
        print('r = {0}(2) = {1}(10)\n'.format(r,
               twos_comp_binary_string_to_int(r)))

    x = len(m)
    y = len(r)
    m = m[0] + m
    A = m + (y+1)*'0'
    S = neg(m)[0] + (y+1)*'0'
    P = '0' + x*'0' + r + '0'

    if rus_output:
        print('Установим значения регистров A, S и P:\n'
              + 'A = {0} {1} {2} {3}\n'.format(A[0], A[1:(x+1)],
                                               A[(x+1):(x+y+1)], A[-1])
              + 'S = {0} {1} {2} {3}\n'.format(S[0], S[1:(x+1)],
                                               S[(x+1):(x+y+1)], S[-1])
              + 'P = {0} {1} {2} {3}\n'.format(P[0], P[1:(x+1)],
                                               P[(x+1):(x+y+1)], P[-1]))
    if rus_output:
        print('P:')
    for _ in range(y):
        two_last_bits_of_p = P[-2:]

        if two_last_bits_of_p == '01':
            P = bsum(A, P)[0]
        elif two_last_bits_of_p == '10':
            P = bsum(S, P)[0]

        P = arithmetic_shift_right(P)
        if rus_output:
            print('{0} {1} {2} {3}'.format(P[0], P[1:(x+1)],
                                           P[(x+1):(x+y+1)], P[-1]))

    if rus_output:
        print('\nОтбрасываем крайние биты. Результат умножения:\n'
              + 'm * r = {0}(2) = {1}(10)'.format(P[1:-1],
                  twos_comp_binary_string_to_int(P[1:-1])))

    return P[1:-1]


def idiv(a, b, rus_output=False):
    if rus_output:
        print('Поделим следующие числа в дополнительном коде:')
        print('a = {0}(2) = {1}(10)'.format(a,
            twos_comp_binary_string_to_int(a)))
        print('b = {0}(2) = {1}(10)\n'.format(b,
            twos_comp_binary_string_to_int(b)))

    if twos_comp_binary_string_to_int(b) == 0:
        print('Ошибка: деление на ноль.')
        raise ZeroDivisionError

    a, b = _align(a, b)
    M = b
    AQ = expand_to_len(a, len(a)*2)
    A, Q = AQ[:len(a)], AQ[-len(a):]

    if rus_output:
        print('Установим значения регистров A, Q и M:')
        print('A: {0}'.format(A))
        print('Q: {0}'.format(Q))
        print('M: {0}\n'.format(M))

        print('A:' + ' '*(len(A) - 2) + ' Q:\n')

    for _ in range(len(a)):
        AQ = shift_left(A + Q)
        A, Q = AQ[:len(a)], AQ[-len(a):]

        old_A = A
        if M[0] == A[0]:
            A = dif(A, M)[0]
        else:
            A = sum(A, M)[0]

        if old_A[0] == A[0] or A == Q == expand_to_len('0', len(A)):
            Q = Q[:-1] + '1'
        else:
            Q = Q[:-1] + '0'
            A = old_A

        if rus_output:
            print('{0} {1}'.format(A, Q))

    r = A
    q = Q if a[0] == b[0] else neg(Q)[0]

    if rus_output:
        print('')
    error_bool = False
    if neg(Q)[1]:
        error_bool = True
        if rus_output:
            print('Произошло переполнение.')

    if rus_output:
        print('Результат деления:\n'
              + 'q = {0}(2) = {1}(10)\n'.format(q,
                  twos_comp_binary_string_to_int(q))
              + 'r = {0}(2) = {1}(10)'.format(r,
                  twos_comp_binary_string_to_int(r)))

    return q, r, error_bool

# binstrings
def int_to_binstring(n, bits=16):
    assert n >= 0 and n < 2**bits

    n_str = ''
    for _ in range(bits):
        n_str = str(n % 2) + n_str
        n //= 2

    return n_str


def binstring_to_int(n_str):
    n = 0
    for bit in n_str:
        if bit == '1':
            n = n*2 + 1
        else:
            n = n*2

    return n


def int_to_twos_comp_binary_string(n, bits=16):
    if n == -(2**(bits - 1)):
        return '1' + '0'*(bits - 1)
    s = ''
    pos = True
    if n < 0:
        pos = False
        n *= -1
    for _ in range(bits - 1):
        bit = n % 2
        n //= 2
        s = str(bit) + s
    s = '0' + s
    if pos:
        return s
    else:
        return neg(s)[0]


def twos_comp_binary_string_to_int(s):
    pos = True
    if s[0] == '1':
        pos = False
        s = neg(s)[0]

    n = 0
    for bit in s:
        if bit != '0' and bit != '1':
            continue
        n = n*2 + (1 if bit == '1' else 0)

    return n if pos else -n


# for binstrings
def is_valid(some_string: str):
    return (set(some_string) == set('01')
            or set(some_string) == set('0')
            or set(some_string) == set('1'))


def is_zero(some_string: str):
    assert is_valid(some_string)

    return set(some_string) == set('0')


def _align(a: str, b: str):
    assert is_valid(a) and is_valid(b)

    while len(a) != len(b):
        if len(a) < len(b):
            a = '0' + a
        else:
            b = '0' + b

    return a, b

def first_is_bigger(a: str, b: str):
    assert is_valid(a) and is_valid(b)

    a, b = _align(a, b)
    for a_bit, b_bit in  zip(a, b):
        if a_bit == '1' and b_bit == '0':
            return True
        elif a_bit == '0' and b_bit == '1':
            return False

    return False