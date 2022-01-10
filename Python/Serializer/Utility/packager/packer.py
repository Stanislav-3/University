from datetime import datetime
from sys import builtin_module_names
from packager.creator import *
from packager.object_inspector import *


class Packer:
    def pack(self, obj: object):
        self.metainfo = {}
        self.proceeded = []
        dump = self.dump(obj)
        if len(self.metainfo) == 0:
            return dump
        else:
            return {".META": self.metainfo, ".OBJ": dump}

    def funcdump(self, obj, isstatic=False):
        obj_id = id(obj)

        if isinstance(obj, staticmethod):
            return self.funcdump(obj.__func__, True)

        function_module = getattr(obj, "__module__", None)

        if function_module != None and function_module in builtin_module_names:
            self.metainfo.update({str(obj_id): {".metatype": "builtin func",
                                                ".name": obj.__name__,
                                                ".module": obj.__module__}})
        else:
            dumped = deconstruct_func(obj)

            code_dict = dumped[".code"]
            code_dict["co_code"] = [el for el in code_dict["co_code"]]
            code_dict["co_lnotab"] = [el for el in code_dict["co_lnotab"]]

            if self.metainfo.get(str(obj_id)) == None:
                self.metainfo.update({str(obj_id): {".code": self.dump(code_dict),
                                                    ".metatype": "func",
                                                    ".name": self.dump(dumped[".name"]),
                                                    ".module": getattr(obj, "__module__", None),
                                                    ".refs": self.dump(dumped[".references"]),
                                                    ".defaults": self.dump(dumped[".defaults"])}})

            return {".metaid": str(obj_id)}

    def dump(self, obj: object):
        if obj is None:
            return None

        if is_primitive(obj):
            return obj

        if type(obj) in [list, set, tuple, dict, frozenset]:
            if isinstance(obj, dict):
                result = {key: self.dump(obj[key]) for key in obj}
            elif type(obj) in [frozenset, set, tuple]:
                result = {".list": [self.dump(el) for el in obj], ".collection_type": f"{obj.__class__.__name__}"}
            else:
                result = [self.dump(el) for el in obj]
            return result

        if isinstance(obj, datetime):
            return {".time": str(obj.isoformat())}

        obj_id = id(obj)
        if obj_id in self.proceeded:
            return {".metaid": str(obj_id)}
        elif not getattr(obj, "__name__", None) in dir(builtins):
            self.proceeded.append(obj_id)

        if inspect.ismodule(obj):
            try:
                if self.metainfo.get(str(obj_id)) == None:
                    if obj.__name__ in builtin_module_names:
                        self.metainfo.update({str(obj_id): {".metatype": "module", ".name": obj.__name__}})
                    else:
                        self.metainfo.update(
                            {str(obj_id): {".code": get_code(obj), ".metatype": "module", ".name": obj.__name__}})
            except Exception:
                self.metainfo.update({str(obj_id): {".metatype": "module", ".name": obj.__name__}})
            return {".metaid": str(obj_id)}

        if getattr(obj, "__name__", None) and not is_basetype(obj):
            if obj.__name__ in dir(builtins):
                try:
                    self.proceeded.remove(str(obj_id))
                except Exception:
                    pass
                return {".metatype": "builtin", ".builtin": obj.__name__}

            if inspect.ismethod(obj) or inspect.isfunction(obj) or isinstance(obj, staticmethod):
                return self.funcdump(obj)

            if inspect.isbuiltin(obj):
                self.metainfo.update(
                    {str(obj_id): {".metatype": "builtin-func", ".module": obj.__module__, ".name": obj.__name__}})
                return {".metaid": str(obj_id)}

            if is_instance(obj):
                type_, fields = deconstruct_instance(obj)
                type_id = id(type_)
                self.dump(type_)

                data = {key: self.dump(fields[key]) for key in fields}
                return {".metaid": str(type_id), ".fields": data}

            if inspect.isclass(obj):
                mro = fetch_type_references(obj)
                attrs = deconstruct_class(obj)
                mro = [self.dump(el) for el in mro]
                attrs = [self.dump((el[0], self.dump(el[1]), el[2])) for el in attrs]

                if self.metainfo.get(str(obj_id)) == None:
                    self.metainfo.update({str(obj_id): {".metatype": "class", ".name": obj.__name__,
                                                        ".module": getattr(obj, "__module__", None),
                                                        ".class": {"mro": mro, "attrs": attrs}}})

                return {".metaid": str(obj_id)}
        else:
            if inspect.ismethod(obj) or inspect.isfunction(obj) or isinstance(obj, staticmethod):
                return self.funcdump(obj)

            if is_instance(obj):
                type_, fields = deconstruct_instance(obj)
                type_id = id(type_)
                self.dump(type_)

                data = {key: self.dump(fields[key]) for key in fields}
                return {".metaid": str(type_id), ".fields": data}

            return None