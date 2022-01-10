import pickle
from database.archive import Archive
from Serializer.factory.parser_factory import create_serializer


class DataManager:
    file_name = 'database/cache.pkl'

    def save_info(self, users, company_info):
        archive = Archive(users, company_info.map, company_info.drivers, company_info.cars,
                          company_info.budget, company_info.orders)

        with open(self.file_name, 'wb') as file:
            pickle.dump(archive, file)

    def initialize(self, users, company_info):
        with open(self.file_name, 'rb') as file:
            archive = pickle.load(file)

        for i in range(len(archive.users)):
            users.append(archive.users[i])

        company_info.map = archive.map
        company_info.drivers = archive.drivers
        company_info.cars = archive.cars
        company_info.budget = archive.budget
        company_info.orders = archive.orders