from abc import ABC


class User(ABC):
    def __init__(self, login, password):
        self.login = login
        self.__password = password

    def set_password(self, password):
        setattr(self.__password , password)

    def get_password(self):
        return self.__password
