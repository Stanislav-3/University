import os

from datetime import datetime
from types import FunctionType, CodeType
from sys import modules
from packager.creator import *
from packager.object_inspector import *


class Unpacker:
    def unpack(self, src: object, __globals__=globals()):
        self._globals = __globals__
        if isinstance(src, dict):
            if src.get(".META") != None and src.get(".OBJ") != None:
                self.metatypes = {}
                self.proceeded = []
                self.metadict = src[".META"]
                return self.load(src[".OBJ"])
            else:
                return self.load(src)

        if src is None:
            return None

        if is_primitive(src):
            return src

        if isinstance(src, list):
            return [self.load(el) for el in src]

    def load(self, src, id_=None):
        if src is None:
            return None

        if is_primitive(src):
            return src

        elif isinstance(src, list):
            return [self.load(el) for el in src]

        elif isinstance(src, dict):
            if src.get(".metaid") != None and src.get(".metatype") == None:
                meta_id = src[".metaid"]
                obj = None

                if src[".metaid"] in self.proceeded:
                    obj = self.metatypes[meta_id]
                else:
                    obj = self.load(self.metadict[meta_id], meta_id)
                    self.metatypes[meta_id] = obj
                    self.proceeded.append(meta_id)
                if src.get(".fields"):
                    obj = create_instance(obj, self.load(src[".fields"]))
                return obj

            elif src.get(".metatype"):
                metatype = src[".metatype"]

                if metatype == "func":
                    if src[".module"] != "__main__":
                        try:
                            exec(f'from {src[".module"]} import {src[".name"]}')
                            return eval(f'{src[".name"]}')
                        except Exception:
                            pass

                    refs = self.load(src[".refs"])
                    nonlocals = refs[0]
                    globals_ = refs[1]

                    co_raw = self.load(src[".code"])

                    co = CodeType(
                        co_raw["co_argcount"],
                        co_raw["co_posonlyargcount"],
                        co_raw["co_kwonlyargcount"],
                        co_raw["co_nlocals"],
                        co_raw["co_stacksize"],
                        co_raw["co_flags"],
                        bytes(co_raw["co_code"]),
                        co_raw["co_consts"],
                        co_raw["co_names"],
                        co_raw["co_varnames"],
                        co_raw["co_filename"],
                        co_raw["co_name"],
                        co_raw["co_firstlineno"],
                        bytes(co_raw["co_lnotab"]),
                        co_raw["co_freevars"],
                        co_raw["co_cellvars"]
                    )

                    for el in globals_:
                        if el in globals().keys():
                            continue
                        else:
                            globals()[el] = self.load(globals_[el])

                    closures = tuple(cell_factory(nonlocals[el]) for el in co.co_freevars)

                    naked = [
                        co,
                        globals(),
                        src[".name"],
                        src[".defaults"],
                        closures
                    ]

                    func = FunctionType(*naked)
                    return func

                if metatype == "builtin-func":
                    try:
                        exec(f'from {src[".module"]} import {src[".name"]}')
                        return eval(f'{src[".name"]}')
                    except Exception:
                        raise KeyError(f'builtin func "{src[".module"]}.{src[".name"]}" import failed')

                elif metatype == "class":
                    if src[".module"] != "__main__":
                        try:
                            exec(f'from {src[".module"]} import {src[".name"]}')
                            return eval(f'{src[".name"]}')
                        except Exception:
                            pass

                    class_info = src[".class"]
                    mro = self.load(class_info["mro"])
                    cls = create_class(src[".name"], mro)

                    self.metatypes[id_] = cls
                    self.proceeded.append(id_)

                    attrs = self.load(class_info["attrs"])

                    return set_class_attrs(cls, attrs)

                elif metatype == "module":
                    try:
                        exec(f'import {src[".name"]}')
                        result = eval(src[".name"])
                        return result
                    except Exception:
                        if ".code" in src.keys():
                            with open("{}/{}.py".format("/".join(modules["__main__"].__file__.split('/')[:-1]),
                                                        src[".name"]), "w") as writer:
                                writer.write(src[".code"])
                            exec(f'import {src[".name"]}')
                            result = eval(src[".name"])
                            os.unlink(
                                "{}/{}.py".format("/".join(modules["__main__"].__file__.split('/')[:-1]), src[".name"]))
                            return result
                    raise KeyError(f'module"{src[".module"]}" import failed')

                elif metatype == "builtin":
                    if src.get(".builtin"):
                        return getattr(builtins, src[".builtin"])
                    else:
                        raise KeyError(f'builtin "{src[".builtin"]}" import failed')

                else:
                    raise KeyError(f"Unexpected metatype: {metatype}")

            elif src.get(".collection_type"):
                if src[".collection_type"] == "tuple":
                    return tuple(el for el in self.load(src[".list"]))
                elif src[".collection_type"] == "set":
                    return set(el for el in self.load(src[".list"]))
                elif src[".collection_type"] == "frozenset":
                    return frozenset(el for el in self.load(src[".list"]))
                else:
                    return self.load(src[".list"])

            elif src.get(".time"):
                date = datetime.fromisoformat(src[".time"])
                return date

            else:
                res = {
                    key: self.load(src[key]) for key in src
                }

                return res