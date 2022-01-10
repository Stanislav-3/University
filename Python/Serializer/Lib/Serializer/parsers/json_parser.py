from typing import Any
from Serializer.parsers.custom_json.json import Json
from Serializer.parsers.base_parser import BaseParser
from Serializer.packager.packer import Packer
from Serializer.packager.unpacker import Unpacker


class JsonParser(BaseParser):
    base_dumps = Json.dumps
    base_loads = Json.loads

    def dump(self, obj: object, file: object = None, pack=True) -> None:
        super().dump(obj, file)

        if pack:
            packed_obj = Packer().pack(obj)
        else:
            packed_obj = obj

        with open(file, 'w') as file:
            file.write(JsonParser.base_dumps(packed_obj))

    def dumps(self, obj: object) -> None:
        super().dumps(obj)
        packed_obj = Packer().pack(obj)
        return JsonParser.base_dumps(packed_obj)

    def load(self, file: object, unpack=True) -> Any:
        super().load(file)

        with open(file, 'r') as file:
            try:
                raw_obj = JsonParser.base_loads(file.read())
            except Exception:
                raise ValueError('Invalid json format...')

        if unpack:
            return Unpacker().unpack(raw_obj)
        else:
            return raw_obj

    def loads(self, json: str) -> Any:
        super().loads(json)

        try:
            raw_obj = JsonParser.base_loads(json)
        except Exception:
            raise ValueError('Invalid json format...')

        unpacked_obj = Unpacker().unpack(raw_obj)
        return unpacked_obj