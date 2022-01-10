from cached import cached


@cached
def simple_func(x, y):
    return x + y


@cached
def full_func(*args, **kwargs):
    sum_ = sum(args)
    sum_ += sum(kwargs.values())

    return sum_


@cached
def compound_func(x, y, *args, **kwargs):
    sum_ = x + y
    sum_ += sum(args)
    sum_ += sum(kwargs.values())

    return sum_
