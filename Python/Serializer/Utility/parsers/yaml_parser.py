import warnings
from yaml import dump, load

from parsers.base_parser import BaseParser
from packager.packer import Packer
from packager.unpacker import Unpacker

warnings.filterwarnings("ignore")

class YamlParser(BaseParser):
    base_dumps = dump
    base_loads = load

    def dump(self, obj: object, file: object = None, unpacked=True):
        super().dump(obj, file)

        if unpacked:
            packed_obj = Packer().pack(obj)
        else:
            packed_obj = obj

        with open(file, 'w') as file:
            file.write(YamlParser.base_dumps(packed_obj))


    def dumps(self, obj: object):
        super().dumps(obj)

        packed_obj = Packer().pack(obj)
        return YamlParser.base_dumps(packed_obj)

    def load(self, file: object, unpack=True):
        super().load(file)

        with open(file, 'r') as file:
            try:
                raw_obj = YamlParser.base_loads(file.read())
            except Exception:
                raise ValueError('Invalid yaml format...')

        if unpack:
            return Unpacker().unpack(raw_obj)
        else:
            return raw_obj

    def loads(self, yaml: str):
        super().loads(yaml)

        try:
            raw_obj = YamlParser.base_loads(yaml)
        except Exception:
            raise ValueError('Invalid yaml format...')

        unpacked_obj = Unpacker().unpack(raw_obj)
        return unpacked_obj