from units.map.graph import Graph
from units.order.order_status import Order_status
from factories.unit_factory import create_unit


class CompanyInfo():
    def __init__(self, map_name = "Belarus", cars = [], drivers = [], budget = [], orders = []):
        self.map = Graph(map_name)
        self.cars = cars
        self.drivers = drivers
        self.budget = budget
        self.orders = orders

    def add_city(self, city1, city2, distance, max_speed):
        self.map.add_nodes(city1, city2, distance, max_speed)

    def delete_city(self, city):
        self.map.delete_node(city)

    def delete_road(self, city1, city2):
        self.map.delete_arc(city1, city2)

    def add_car(self, model, gas_consumtion, max_load):
        try:
            car = create_unit('car', model, gas_consumtion, max_load)
            self.cars.append(car)
        except Exception as e:
            raise Exception('A problem occurred!\n'
                            + f'Car is not added!\n{e}')

    def add_driver(self, name, middle_name, surname, experience):
        try:
            driver = create_unit('Driver', name, middle_name, surname, float(experience))
            self.drivers.append(driver)
        except Exception as e:
            raise Exception('A problem occurred!\n'
                            + f'Driver is not added!\n{e}')

    def add_budget(self, income, date1, date2=None):
        if date2 is None:
            budget = create_unit('Budget', income, date1)
        else:
            budget = create_unit('Budget', income, date1, date2)

        self.budget.append(budget)

    def add_order(self, origin, destination, arrival_date, load, experience_matters):
        order = create_unit('Order', origin, destination, arrival_date, load, experience_matters)
        self.orders.append(order)

        return order

    # Orders thing
    def get_available_car(self, load):
        car = None
        for i in range(len(self.cars)):
            if self.cars[i].max_load < load or not self.cars[i].is_available:
                continue

            if car is None:
                car = self.cars[i]
            elif self.cars[i].gas_consumption < car.gas_consumption:
                car = self.cars[i]

        if car is None:
            raise Exception('No available car')

        return car

    def get_available_driver(self, experience_matters = True):
        driver = None
        for i in range(len(self.drivers)):
            if not self.drivers[i].is_available:
                continue

            if driver is None:
                driver = self.drivers[i]
            elif experience_matters and self.drivers[i].driving_experience > driver.driving_experience\
                or not experience_matters and self.drivers[i].driving_experience < driver.driving_experience:
                driver = self.drivers[i]

        if driver is None:
            raise Exception('No available driver')

        return driver

    def get_orders(self, comporator: Order_status):
        orders = []
        for i in range(len(self.orders)):
            if self.orders[i].compare_status(comporator):
                orders.append(self.orders[i])

        return orders