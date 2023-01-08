from CustomRandom import rand
import numpy as np
import time


def gen1(p: float):
    return rand() < p


def gen2(p: list):
    return [gen1(p_i) for p_i in p]


def gen3(p_A: float, p_B_when_A: float):
    if gen1(p_A):
        return 0 if gen1(p_B_when_A) else 1
    else:
        return 2 if gen1(1 - p_B_when_A) else 3


def gen4(p: list):
    assert sum(p) == 1

    value = rand()
    s = 0.
    for i, p_i in enumerate(p):
        s += p_i
        if s > value:
            return i


def validate(current_generator, text_input):
    if current_generator == 1:
        number = float(text_input)
        if number < 0 or number > 1:
            raise ValueError('Probability should be in [0, 1] range')

        return number

    if current_generator == 2:
        numbers = [number.strip() for number in text_input.split(',')]
        numbers = [float(i) for i in numbers]
        for number in numbers:
            if number < 0 or number > 1:
                raise ValueError('Probability should be in [0, 1] range')

        return numbers

    if current_generator == 3:
        numbers = [number.strip() for number in text_input.split(',')]
        numbers = [float(i) for i in numbers]
        for number in numbers:
            if number < 0 or number > 1:
                raise ValueError('Probability should be in [0, 1] range')

        if len(numbers) != 2:
            raise ValueError('You should enter 2 floats')

        return numbers

    if current_generator == 4:
        numbers = [number.strip() for number in text_input.split(',')]
        numbers = [float(i) for i in numbers]
        for number in numbers:
            if number < 0 or number > 1:
                raise ValueError('Probability should be in [0, 1] range')

        if sum(numbers) != 1:
            raise ValueError('Probabilities sum should equal to 1')

        return numbers


def compute(current_generator, text_input):
    N = 10 ** 6

    if current_generator == 1:
        try:
            number = validate(current_generator, text_input)
        except Exception as e:
            raise

        result = [0., 0.]
        for i in range(N):
            result[int(gen1(number))] += 1 / N

        return result

    if current_generator == 2:
        try:
            numbers = validate(current_generator, text_input)
        except Exception as e:
            raise

        t0 = time.time()

        result = np.zeros(len(numbers))
        for i in range(N):
            result += np.array(gen2(numbers))

        print('Time: ', time.time() - t0)
        return (result / N).tolist()

    if current_generator == 3:
        try:
            numbers = validate(current_generator, text_input)
        except Exception as e:
            raise

        result = [0, 0, 0, 0]
        for i in range(N):
            result[gen3(*numbers)] += 1 / N

        P_A, P_B_when_A = numbers

        P_AB = P_A * P_B_when_A
        P_not_A_B = (1 - P_A) * (1 - P_B_when_A)
        P_A_not_B = (1 - P_B_when_A) * P_A
        P_not_A_not_B = P_B_when_A * (1 - P_A)

        analytical_result = (P_AB, P_A_not_B, P_not_A_B, P_not_A_not_B)
        return result, analytical_result

    if current_generator == 4:
        try:
            numbers = validate(current_generator, text_input)
        except Exception as e:
            return e

        result = [0.] * len(numbers)
        for i in range(N):
            result[gen4(numbers)] += 1 / N

        return result
