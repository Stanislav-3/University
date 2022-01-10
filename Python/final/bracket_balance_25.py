def matches(ch1, ch2) -> bool:
    if (ch1 == '{' and ch2 == '}') or (ch1 == '[' and ch2 == ']') or (ch1 == '(' and ch2 == ')'):
        return True

    return False


def check_brackets(s: str):
    brackets = []
    for ch in s:
        if ch == '{' or ch == '[' or ch == '(':
            brackets.append(ch)
        if ch == '}' or ch == ']' or ch == ')':
            if len(brackets) != 0:
                bracket = brackets.pop()
            else:
                bracket = None

            if not matches(bracket, ch):
                raise SyntaxError(f"Brackets {bracket} and {ch} doesn't match")

    if len(brackets) != 0:
        raise SyntaxError(f"Brackets doesn't match")
