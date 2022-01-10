from inspect import getsourcelines
from abc import ABC


class ClassCreator(ABC):
    @staticmethod
    def create(name, mro):
        globals().update({el.__name__: el for el in mro[0]})
        if len(mro[0]) != 0:
            bases = ','.join([base.__name__ for base in mro[0]])
        else:
            bases = ''

        if mro[1]:
            globals().update({mro[1].__name__: mro[1]})
            meta = 'metaclass=' + mro[1].__name__
        else:
            meta = ''

        if bases != '':
            str_ = bases + ", " + meta
        else:
            str_ = meta
        exec(f"class {name}({str_}):\n\tpass")
        return eval(f"{name}")


def set_class_attrs(cls, attributes=None):
    if attributes is None:
        return cls

    for attr in attributes:
        if attr[1] != None:
            try:
                if attr[2] == "static method":
                    setattr(cls, attr[0], staticmethod(attr[1]))
                elif attr[2] == "class method":
                    setattr(cls, attr[0], classmethod(attr[1]))
                else:
                    setattr(cls, attr[0], attr[1])
            except AttributeError:
                continue
    return cls


def create_class(name, mro=None, attributes=None):
    template = ClassCreator.create(name, mro)
    if attributes is None:
        return template

    return set_class_attrs(template, attributes)


def create_instance(type_, fields):
    instance = type_.__new__(type_)
    for el in fields:
        setattr(instance, el, fields[el])

    return instance


def cell_factory(el):
    inner_el = el
    def inner():
        return inner_el

    return inner.__closure__[0]


def get_code(obj):
    lines = getsourcelines(obj)[0]
    indent = len(lines[0]) - len(lines[0].lstrip())

    new_lines = []
    for line in lines:
        if len(line) >= indent:
            line = line[indent:]

        new_lines.append(line)
    return '\n'.join(new_lines)