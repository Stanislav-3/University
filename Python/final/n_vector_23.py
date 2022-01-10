import math


class Vector(object):
    def __init__(self, *args):
        self.values = list(args)

    def __iter__(self):
        self.counter = 0
        return self

    def __next__(self):
        if self.counter < len(self.values):
            temp = self.counter
            self.counter += 1
            return self.values[temp]
        else:
            raise StopIteration()

    def __getitem__(self, item):
        return self.values[item]

    def __add__(self, other):
        return Vector(*((a + b) for a, b in zip(self.values, other)))

    def __iadd__(self, other):
        for i in range(0, len(self.values)):
            self.values[i] += other[i]
        return self

    def __mul__(self, other):
        if type(other) is Vector:
            return Vector(*((a * b) for a, b in zip(self.values, other.values)))
        else:
            return Vector(*((a * other) for a in self.values))

    def __imul__(self, other):
        for i in range(0, len(self.values)):
            self.values[i] *= other
        return self

    def __eq__(self, other):
        return self.values == other.values

    def __len__(self):
        return len(self.values)

    def modulus(self):
        return math.sqrt(sum(a ** 2 for a in self.values))

    def __str__(self):
        return str(self.values)