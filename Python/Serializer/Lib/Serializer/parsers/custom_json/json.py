from abc import ABC
from Serializer.parsers.custom_json import decoder


class Json():
    @staticmethod
    def dumps(obj):
        if obj is None:
            return 'null'

        obj_type = type(obj)
        if obj_type is bool:
            return f'{str(obj).lower()}'

        if obj_type is int or obj_type is float:
            return f'{obj}'

        if obj_type is str:
            return f'"{obj}"'

        if obj_type is tuple or obj_type is list:
            res = ''
            for i in range(len(obj)):
                res += ', ' + Json.dumps(obj[i])

            return '[' + res[2:] + ']'

        if obj_type is dict:
            res = ''
            for key in obj:
                key_ = Json.dumps(key)
                value_ = Json.dumps(obj[key])
                if key_[0] != '"':
                    key_ = f'"{key_}"'

                res += f', {key_}: {value_}'

            return '{' + res[2:] + '}'

        raise TypeError(f'Object of type {obj_type.__name__} is not JSON serializable')

    @staticmethod
    def dump(obj, fp):
        with open(fp, 'w') as file:
            file.write(Json.dumps(obj))

    @staticmethod
    def loads(s):
        if s == 'null':
            return None

        if decoder.is_bool(s):
            return decoder.to_bool(s)

        if decoder.is_number(s):
            return decoder.to_number(s)

        if decoder.is_str(s):
            return s[1:-1]

        if decoder.is_arr(s):
            arr = []
            split = decoder.split_arr(s)
            for i in range(len(split)):
                arr.append(Json.loads(split[i]))

            return arr

        if decoder.is_dict(s):
            d = {}
            split = decoder.split_dict(s)
            for i in range(len(split)):
                key = Json.loads(split[i][0])
                if isinstance(key, list):
                    key = tuple(key)

                d[key] = Json.loads(split[i][1])

            return d

        raise TypeError(f"{s} cannot be converted to an object")

    @staticmethod
    def load(fp):
        with open(fp, 'r') as file:
            return Json.loads(file.read())

