from Serializer.parsers.json_parser import JsonParser
from Serializer.parsers.yaml_parser import YamlParser

serializers = {
    "json": JsonParser,
    "yaml": YamlParser,
    "toml": None,
    "pickle": None
}

def create_serializer(file_format: str):
    serializer = serializers.get(file_format.lower(), None)
    if serializer is None:
        raise ValueError(f'File format \'{file_format}\' is not supported...')

    return serializer()