import re


def is_bool(s: str) -> bool:
    if s == 'true' or s == "false":
        return True

    return False


def to_bool(s: str) -> bool:
    if not is_bool(s):
        raise TypeError(f"String '{s}' cannot be converted to 'bool'")

    if s == 'true':
        return True
    else:
        return False


def is_number(s: str) -> bool:
    match = re.match('\d+\.?\d*', s)
    if match is None or match.group() != s:
        return False
    else:
        return True


def to_number(s: str):
    if not is_number(s):
        raise TypeError(f"String '{s}' cannot be converted to 'int' or 'float'")

    if s.find('.') == -1:
        return int(s)
    else:
        return float(s)


def is_str(s: str) -> bool:
    if s[0] == '"' and s[-1] == '"':
        return True

    return False


def is_arr(s: str) -> bool:
    if s[0] == '[' and s[-1] == ']':
        return True

    return False


def is_dict(s: str) -> bool:
    if s[0] == '{' and s[-1] == '}':
        return True

    return False


def matches(ch1, ch2) -> bool:
    if ch1 == '{' and ch2 == '}' or ch1 == '[' and ch2 == ']':
        return True

    return False


def manage_brackets(ch: str, brackets: list):
    if ch == '{' or ch == '[':
        brackets.append(ch)
    if ch == '}' or ch == ']':
        bracket = brackets.pop()
        if not matches(bracket, ch):
            raise Exception(f"Invalid JSON format! Brackets {bracket} and {ch} doesn't match")


def split_arr(s: str):
    s = s[1:-1]
    elements = []
    brackets = []
    start_i = 0

    for i in range(len(s)):
        manage_brackets(s[i], brackets)

        if s[i] == ',' and len(brackets) == 0:
            elements.append(s[start_i:i])
            start_i = i + 2

    if len(s):
        elements.append(s[start_i:])

    return elements


def split_dict(s: str):
    s = s[1:-1]
    elements = []
    brackets = []

    key, value = None, None
    out_expr = True
    start_i = 0

    for i in range(len(s)):
        manage_brackets(s[i], brackets)

        if s[i] == '"':
            out_expr = not out_expr

        if s[i] == ':' and out_expr and len(brackets) == 0:
            key = s[start_i:i]
            start_i = i + 2

        if s[i] == ',' and out_expr and len(brackets) == 0:
            value = s[start_i:i]
            start_i = i + 2
            elements.append((key, value))

    if len(s):
        value = s[start_i:]
        elements.append((key, value))

    return elements
