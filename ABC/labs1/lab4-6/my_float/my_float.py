from copy import deepcopy
import numpy as np
import struct

import funcs as f

TOTAL_BIT_COUNT = 32
MANTISSA_BIT_COUNT = 23
EXPONENT_BIT_COUNT = 8


class Float:
    @staticmethod
    def float_to_bin(num):
        return (''.join(bin(c).replace('0b', '').rjust(8, '0')
                        for c in struct.pack('!f', num)))

    @staticmethod
    def bin_to_float(b: str):
        f = int(b, 2)
        return np.float32(struct.unpack('f', struct.pack('I', f))[0])

    @staticmethod
    def pos_zero():
        return Float(0.)

    @staticmethod
    def neg_zero():
        return Float(-0.)

    @staticmethod
    def pos_infinity():
        return Float(float('inf'))

    @staticmethod
    def neg_infinity():
        return Float(float('-inf'))

    @staticmethod
    def nan():
        return Float(float('nan'))

    # standart methods for classes:
    def __init__(self, num: float):
        self.binary = self.float_to_bin(num)

    def __str__(self):
        return str(self.bin_to_float(self.binary))

    # properties:
    @property
    def sign_bit(self):
        return self.binary[0]

    @sign_bit.setter
    def sign_bit(self, value: str):
        assert f.is_valid(value) and len(value) == 1
        self.binary = value + self.binary[1:]

    @property
    def exponent(self):
        return self.binary[1:(1 + EXPONENT_BIT_COUNT)]

    @exponent.setter
    def exponent(self, value: str):
        assert f.is_valid(value) and len(value) == EXPONENT_BIT_COUNT

        self.binary = self.sign_bit + value + self.mantissa_binary

    @property
    def mantissa_binary(self):
        return self.binary[(1 + EXPONENT_BIT_COUNT):]

    @mantissa_binary.setter
    def mantissa_binary(self, value: str):
        assert f.is_valid(value) and len(value) == MANTISSA_BIT_COUNT
        self.binary = self.sign_bit + self.exponent + value

    @property
    def mantissa(self):
        return ('0' if self.is_denormal() else '1') + self.mantissa_binary

    def is_zero(self):
        return set(self.binary[1:]) == set('0')

    def is_infinity(self):
        return (set(self.exponent) == set('1')
                and set(self.mantissa_binary) == set('0'))

    def is_nan(self):
        return (set(self.exponent) == set('1')
                and set(self.mantissa_binary) == set('01'))

    def is_normal(self):
        return (set(self.exponent) == set('01')
                and set(self.mantissa_binary) == set('01'))

    def is_denormal(self):
        return (set(self.exponent) == set('0')
                and set(self.mantissa_binary) == set('01'))

    # comparison operators:
    def __eq__(self, other):
        if (self.is_normal() or other.is_normal()
                or self.is_denormal() or other.is_denormal()):
            return self.binary == other.binary

        if self.is_zero() and other.is_zero():
            return True

        if self.is_infinity() and other.is_infinity():
            return self.sign_bit == other.sign_bit

        return False

    def __ne__(self, other):
        return not (self == other)

    def __gt__(self, other):
        if self.is_nan() or other.is_nan():
            return False

        if self.is_zero() and other.is_zero():
            return False

        if self.sign_bit != other.sign_bit:
            return self.sign_bit == '0'

        if self.sign_bit == '0':
            return f.first_is_bigger(self.abs().binary,
                                              other.abs().binary)
        else:
            return f.first_is_bigger(other.abs().binary,
                                              self.abs().binary)

    def __ge__(self, other):
        return self > other or self == other

    def __lt__(self, other):
        if self.is_nan() or other.is_nan():
            return False

        return not (self >= other)

    def __le__(self, other):
        if self.is_nan() or other.is_nan():
            return False

        return not (self > other)

    # unary arithmetic operators:
    def __neg__(self):
        negged = deepcopy(self)
        negged.sign_bit = '1' if (negged.sign_bit == '0') else '0'
        return negged

    def abs(self):
        abs_val = deepcopy(self)
        abs_val.sign_bit = '0'
        return abs_val

    # binary arithmetic operators:
    def __add__(self, other):
        print("*** Sum ***")
        print("1) Checking for nan, zero and infinity values...")
        if self.is_nan() or other.is_nan():
            return Float(float('nan'))

        if self.is_infinity() and other.is_infinity():
            if self.sign_bit != other.sign_bit:
                return self.nan
            else:
                return deepcopy(self)

        if self.is_infinity():
            return deepcopy(self)
        elif other.is_infinity():
            return deepcopy(other)

        if self.is_zero():
            return deepcopy(other)
        elif other.is_zero():
            return deepcopy(self)

        # step 2: deconstructing arguments' binaries:
        print("2) Checking a need in swapping values (correct| first <= second)...", end=" | ")
        # bigger, smaller = (self, other) if (self.abs() >= other.abs()) else (other, self)
        bigger = other
        smaller = self
        if self.abs() >= other.abs():
            bigger, smaller = (self, other)
            print(f"{bigger}, {smaller} --> {smaller}, {bigger}")
        else:
            print(f"No need in swapping")

        biggers_sign = bigger.sign_bit
        smallers_sign = smaller.sign_bit

        biggers_exponent = bigger.exponent
        smallers_exponent = smaller.exponent

        biggers_mantissa = bigger.mantissa
        smallers_mantissa = smaller.mantissa

        # step 3: aligning the exponents:
        print("3) Checking the exponent alignment...", end=" | ")
        allign = False
        prev_exponent = smallers_exponent
        prev_mantissa = smallers_mantissa
        while biggers_exponent != smallers_exponent:
            allign = True
            smallers_exponent = f.bsum(smallers_exponent, '01')[0]
            smallers_mantissa = f.logical_shift_right(
                smallers_mantissa)
            if f.is_zero(smallers_mantissa):
                print()
                return deepcopy(bigger)
        if allign == True:
            print(f"smaller's exponent = {prev_exponent} --> {smallers_exponent},"
                  f"\n   smaller's mantissa: {prev_mantissa} --> {smallers_mantissa}")
        else:
            print(f"No need in aligning")

        # step 4: getting mantissas' sum and setting up
        print("4) Getting mantissas' sum", end=" | ")
        sum_sign = biggers_sign
        sum_exponent = biggers_exponent
        sum_mantissa = (f.bsum(biggers_mantissa, smallers_mantissa)
                        if biggers_sign == smallers_sign
                        else f.oc_sum(biggers_mantissa,
                                          f.invert_bits(smallers_mantissa)))

        if type(sum_mantissa) is tuple:
            if sum_mantissa[1]:
                sum_mantissa = '1' + sum_mantissa[0][:-1]
                sum_exponent = f.bsum(sum_exponent, '01')[0]

                if sum_exponent == '1' * EXPONENT_BIT_COUNT:
                    return (Float(float('inf'))
                            if sum_sign == '0'
                            else Float(float('-inf')))
            else:
                sum_mantissa = sum_mantissa[0]

        if sum_mantissa == 24 * "1":
            sum_mantissa = 24 * "0"
        print(f"({smallers_mantissa} + {biggers_mantissa}) * 2 ^ {biggers_exponent} "
              f"\n   = {sum_mantissa} * 2 ^ {sum_exponent}")
        if (f.is_zero(sum_mantissa)):
            return Float(0.)

        # step 5: normalize the number if possible.
        print("5) Normalizing the number if it is needed...", end=" | ")
        norm = False
        prev_r_m = sum_mantissa
        prev_r_e = sum_exponent
        while sum_mantissa[0] == '0':
            norm = True
            sum_mantissa = f.shift_left(sum_mantissa)
            sum_exponent = f.sum(sum_exponent, '11')[0]
            if sum_exponent == '0' * EXPONENT_BIT_COUNT:
                return Float(0.)

        if norm == True:
            print(f"exponent = {prev_r_e} --> {sum_exponent},"
                  f"\n   mantissa: {prev_r_m} --> {sum_mantissa}")
        else:
            print(f"No need in normilizing")

        sum_binary = sum_sign + sum_exponent + sum_mantissa[1:]
        sum_float = deepcopy(self)
        sum_float.binary = sum_binary
        return sum_float

    def __sub__(self, other):
        return self + (-other)

    def __mul__(self, other):
        print("*** Multiplication ***")
        print("1) Checking for zero values...")
        if self.is_zero() or other.is_zero():
            return Float(0.)

        sign_one = self.sign_bit
        exponent_one = self.exponent
        mantissa_one = self.mantissa

        sign_two = other.sign_bit
        exponent_two = other.exponent
        mantissa_two = other.mantissa

        prod_sign = '0' if sign_one == sign_two else '1'

        # step 2: get exponents' sum.
        print("2) Getting exponents' sum...", end=" | ")
        exponent_sum = f.bsum(exponent_one, exponent_two)
        exponent_sum = ('0'
                        + ('1' if exponent_sum[1] else '0')
                        + exponent_sum[0])
        exponent_sum = f.bsum(exponent_sum, '01')[0]
        exponent_sum = f.dif(exponent_sum, '0' + '1' * (EXPONENT_BIT_COUNT - 1))[0]
        print(f"{exponent_one} + {exponent_two} = {exponent_sum}")

        if set(exponent_sum[:2]) != set('0'):
            return (self.pos_infinity()
                    if (prod_sign == '0')
                    else self.neg_infinity())

        prod_exponent = exponent_sum[2:]

        # step 3: get mantissas' 48-bit product.
        print("3) Getting mantissas' product...", end=" | ")
        prod_mantissa = f.imul('0' + mantissa_one, '0' + mantissa_two)[2:]
        print(f"{mantissa_one} * {mantissa_two}\n   = {prod_mantissa}")

        # step 4: normalize the result.
        print("4) Normalizing the number if it is needed...", end=" | ")
        norm = False
        prev_p_e = prod_exponent
        prev_p_m = prod_mantissa[:(MANTISSA_BIT_COUNT + 1)]
        while (prod_mantissa[0] == '0'
               and prod_exponent != '0' * EXPONENT_BIT_COUNT):
            norm = True
            prod_mantissa = f.shift_left(prod_mantissa)
            # decrementing exponent:
            prod_exponent = f.sum(prod_exponent, '11')[0]

        prod_mantissa = prod_mantissa[:(MANTISSA_BIT_COUNT + 1)]
        if norm == True:
            print(f"exponent = {prev_p_e} --> {prod_exponent},"
                  f"\n   mantissa: {prev_p_m} --> {prod_mantissa}")
        else:
            print(f"No need in normalizing")


        # finally return the result.
        prod_binary = prod_sign + prod_exponent + prod_mantissa[1:]
        prod = deepcopy(self)
        prod.binary = prod_binary

        return prod

    def __truediv__(self, other):
        print("*** Division ***")
        print("1) Checking for zero values...")
        if self.is_zero() and not other.is_zero():
            return Float(0.)
        elif not self.is_zero() and other.is_zero():
            return Float(float('inf')) if self.sign_bit == "0" else Float(float('-inf'))
        elif self.is_zero() and other.is_zero():
            # return self.nan
            return Float(float('nan'))

        sign_one = self.sign_bit
        exponent_one = self.exponent
        mantissa_one = self.mantissa

        sign_two = other.sign_bit
        exponent_two = other.exponent
        mantissa_two = other.mantissa

        q_sign = '0' if sign_one == sign_two else '1'

        # step 2: calculating the difference of exponents.
        print("2) Calculating the difference of exponents...", end=" | ")
        exponent_dif = f.dif('0' + exponent_one, '0' + exponent_two)[0]
        exponent_dif = f.sum(exponent_dif,
                                '0' + '1' * (EXPONENT_BIT_COUNT - 1))[0]
        print(f"|{exponent_one} - {exponent_two}| = {exponent_dif}")
        if exponent_dif[0] == '1':
            if f.first_is_bigger(exponent_one, exponent_two):
                return (self.pos_infinity()
                        if q_sign == '0'
                        else self.neg_infinity())
            else:
                return (self.pos_zero()
                        if q_sign == '0'
                        else self.neg_zero())

        q_exponent = exponent_dif[1:]

        # step 3: divide mantissas.
        print("3) Divide mantissas...", end=" | ")
        mantissa_one_double = mantissa_one + '0' * MANTISSA_BIT_COUNT
        q_mantissa = f.idiv('0' + mantissa_one_double, '0' + mantissa_two)[0][-24:]
        print(f"{mantissa_one} / {mantissa_two}|\n   = {q_mantissa}")

        # step 4: normalize the result.
        print("4) Normalizing the number if it is needed...", end=" | ")
        norm = False
        prev_q_e = q_exponent
        prev_q_m = q_mantissa
        while q_mantissa[0] == '0' and q_exponent != '0' * EXPONENT_BIT_COUNT:
            norm = True
            q_mantissa = f.shift_left(q_mantissa)
            q_exponent = f.sum(q_exponent, '11')[0]

        if norm == True:
            print(f"exponent = {prev_q_e} --> {q_exponent},"
                  f"\n   mantissa: {prev_q_m} --> {q_mantissa}")
        else:
            print(f"No need in normalizing")

        q_binary = q_sign + q_exponent + q_mantissa[1:]
        q = deepcopy(self)
        q.binary = q_binary

        return q