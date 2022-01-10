def fibonacci_numbers(amount):
    prev, curr = 0, 1
    for _ in range(amount):
        yield curr
        prev, curr = curr, prev + curr