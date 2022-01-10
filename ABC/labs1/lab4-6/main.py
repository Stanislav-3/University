import itertools

def IEEE754_to_dec(num: str):
    sign = num[0]
    exponent = num[1:9]
    mantissa = num[9:32]
    exponent = int(exponent, 2) - 127
    mantissa = "1" + mantissa
    number = 0
    for i in range(len(mantissa)):
        number += int(mantissa[i]) * 2 ** exponent
        exponent -= 1
    if sign == "1":
        number *= -1
    return number

def frac_to_bin(num: str, n:int):
    num = float(num)
    number = ""
    for i in range(n):
        num = 2 * num
        number += str(int(num))
        num = num - int(num)
    return number

def dec_to_IEEE754(num):
    number = ""
    int_part = num[0]
    frac_part = ""
    try:
        frac_part = num[1]
    except:
        pass
    print(f"Convert number {int_part}.{frac_part} to 32bit IEEE754:", end="\t")
    if int_part[0] == "-":
        number += "1"
        int_part = int_part.replace("-", "")
    else:
        number += "0"
    int_part = bin(int(int_part))[2:]
    if frac_part != '':
        frac_part = frac_to_bin("0." + frac_part, 1000)
    exp = len(int_part) - 1
    if int_part == "0":
        int_part = ""
        exp = -(frac_part.find("1") + 1)
        frac_part = frac_part[frac_part.find("1"):frac_part.find("1") + 24]
    if frac_part == "":
        frac_part = 24 * "0"
    exp += 127
    exp_bin = bin(exp)[2:]
    number += (8 - len(exp_bin)) * "0" + exp_bin
    number += (int_part + frac_part)[1:24]
    # print("Sign:", number[:1], end=" | ")
    # print("Exponent:", number[1:9], end=" | ")
    # print("Mantissa:", number[9:])
    # print("Number:", number)
    print(number)
    return number

def is_zero(string: str):
    sign_bit = string[:1]
    string = string[1:]

    if string != len(string) * "0":
        return 0
    elif sign_bit == "1":
        return -1
    else:
        return 1

def is_infinity(string: str):
    sign_bit = string[:1]
    order = string[1:9]
    mantissa = string[9:32]

    if order != len(order) * "1" or mantissa != len(mantissa) * "0":
        return 0
    elif sign_bit == "1":
        return -1
    else:
        return 1

def is_NaN(string: str):
    order = string[1:9]
    mantissa = string[9:32]

    if order != len(order) * "1" or mantissa == len(mantissa) * mantissa[0]:
        return False
    else:
        return True

def sum_float(num1:str, num2:str):
    if abs(is_zero(num1)) == 1:
        return num2
    if abs(is_zero(num2)) == 1:
        return num1

    if int(num1[1:9], 2) > int(num2[1:9], 2):
        num1, num2 = num2, num1
    # num1 - min & num2 - max
    sign1 = num1[0]
    exponent1 = num1[1:9]
    mantissa1 = "1" + num1[9:32]
    sign2 = num2[0]
    exponent2 = num2[1:9]
    mantissa2 = "1" + num2[9:32]

    # make exponents equal
    if exponent1 != exponent2:
        dx = int(exponent2, 2) - int(exponent1, 2)
        exponent1 = exponent2
        mantissa1 = "0" * dx + mantissa1[:len(mantissa1) - dx]
        if mantissa1 == "0" * len(mantissa1):
            return sign2 + exponent2 + mantissa2

    # sum mantissas
    mantissa, overflow = sum_int(twos_complement(sign1 + mantissa1), twos_complement(sign2 + mantissa2))
    # maybe swap lines
    sign = mantissa[:1]
    mantissa = twos_complement(mantissa)[1:]
    if mantissa == "0" * len(mantissa):
        return "0" * 32
    exponent = exponent2
    if overflow == True:
        mantissa = "1" + mantissa[len(mantissa) - 1:]
        if int(exponent, 2) == 255:
            return "Overflow exception..."
        else:
            exponent = bin(int(exponent, 2) + 1)[2:]

    dx = mantissa[1:].find("1")
    mantissa = mantissa[1 + dx:]
    mantissa += "0" * (23 - len(mantissa))
    if int(exponent1, 2) - dx < 0:
        return "Underflow exception..."
    else:
        exponent = bin(int(exponent1, 2) - dx)[2:]

    return sign + exponent + mantissa

def twos_complement(string):
    number = string[0]
    if number == "0":
        return string
    for i in range(len(string[1:])):
        if string[i + 1] == "0":
            number += "1"
        else:
            number += "0"
    number = sum_int(number, "1")[0]
    return number

def sum_int(a, b):
    c = ''
    extra_bit = False
    for a_bit, b_bit in itertools.zip_longest(reversed(a), reversed(b)):
        if bool(b_bit == '1') != extra_bit:
            if a_bit == '0' or a_bit is None:
                c = '1' + c
                extra_bit = False
            else:
                c = '0' + c
                extra_bit = True
        else:
            c = (a_bit if a_bit is not None else '0') + c
    return c, extra_bit

if __name__ == '__main__':
    first = (input("First number: ") + ".").split(".")
    second = input("Second number: ").split(".")
    # first = IEEE754_to_dec("0100" + "0010" + "0000" + "1111" + 4 * "0000").split(".")
    # second = IEEE754_to_dec("0100" + "0001" + "1010" + "0100" + 4 * "0000").split(".")

    first = dec_to_IEEE754(first)
    second = dec_to_IEEE754(second)

    # if first == "0100" + "0010" + "0000" + "1111" + 4 * "0000":
    #     print("correct")
    # if second == "0100" + "0001" + "1010" + "0100" + 4 * "0000":
    #     print("correct")
    print(sum_int("1100", "0010"))
    print(sum_float(first, second))
    print(IEEE754_to_dec(sum_float(first, second)))
