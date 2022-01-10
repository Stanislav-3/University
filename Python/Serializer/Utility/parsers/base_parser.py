from abc import ABC, abstractmethod


class BaseParser(ABC):
    @abstractmethod
    def dump(self, obj, fp):
        """
        Serialize object and put the result to file.
        """
        if fp is None:
            raise ValueError("File transfer aborted")


    @abstractmethod
    def dumps(self, obj):
        """
        Returns string with serialized object.
        """
        pass


    @abstractmethod
    def load(self, fp):
        """
        Returns parsed object and data from the file.
        """
        if fp is None:
            raise ValueError("File transfer aborted")


    @abstractmethod
    def loads(self, s):
        """
        Returns parsed object and data from the string.
        """
        pass