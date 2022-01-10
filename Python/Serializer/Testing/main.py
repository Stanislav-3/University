from tests import *
from Serializer.factory.parser_factory import create_serializer
import math

def f(x, y):
    return x + math.sin(y)


if __name__ == '__main__':
    serializer = create_serializer('json')

    res = serializer.dumps(f)
    print(res)
    func = serializer.loads(res)

    print(func(1, 3))
