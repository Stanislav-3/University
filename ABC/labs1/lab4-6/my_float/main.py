import my_float as mf

if __name__ == '__main__':
    _first = float(input("First number: "))
    _second = float(input("Second number: "))
    first = mf.Float(_first)
    second = mf.Float(_second)
    print(f"Convert {_first} to bin IEEE 754:\t", first.binary)
    print(f"Convert {_second} to bin IEEE 754:\t", second.binary)

    sum = first + second
    print("Result:")
    print(f"{first.binary} + {second.binary}\n=", sum.binary)
    print(f"{_first} + {_second} = ", sum)
    print()

    mul = first * second
    print("Result:")
    print(f"{first.binary} * {second.binary}\n=", mul.binary)
    print(f"{_first} * {_second} = ", mul)
    print()

    div = first / second
    print("Result:")
    print(f"{first.binary} / {second.binary}\n=", div.binary)
    print(f"{_first} / {_second} = ", div)
    print()


