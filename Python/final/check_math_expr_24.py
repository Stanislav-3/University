import bracket_balance_25
import re


def check_math_expression(expr: str):
    try:
        check_math_expression(expr)
        if not re.fullmatch(r'[\d+-/*(){}\[\]]*', expr):
            raise SyntaxError('Not matches with regex')

    except SyntaxError as e:
        raise SyntaxError(f'Invalid expression:\n'
                          f'{e}')