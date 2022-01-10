from users.user import User
from datetime import datetime, timedelta
from company_info import Order_status

class Operator(User):
    def get_map(self, map):
        title = "City 1\tCity 2 (Distance [km], Max speed [km/h])"
        info = []
        line = None
        for i in range(len(map.nodes)):
            line = f"{map.nodes[i].name:}\t"
            for j in range(len(map.nodes[i].neighbors)):
                line += f"{map.nodes[i].neighbors[j][0]}" \
                        f"({map.nodes[i].neighbors[j][1].distance}, {map.nodes[i].neighbors[j][1].max_speed}) | "
            info.append(line)

        return (title, info)

    def get_drivers(self, drivers):
        title = "Name\tMid name\tSurname\tExperience\tAvailability"
        info = []
        for driver in drivers:
            availablity = '+' if driver.is_available == True else '-'
            info.append(f'{driver.name}\t{driver.middle_name}\t{driver.surname}\t{driver.driving_experience}\t{availablity}')

        return (title, info)

    def get_cars(self, cars):
        title = "Model\tConsumption[l/km]\tMax speed[km/h]\tAvailability"
        info = []
        for car in cars:
            availablity = '+' if car.is_available == True else '-'
            info.append(f'{car.model}\t{car.gas_consumption}\t\t{car.max_load}\t\t{availablity}')

        return (title, info)

    def get_budget(self, budget):
        title = "Income\t\tDate"
        info = []
        for bargain in budget:
            info.append(f'{bargain.income}$\t\t'
                        f'{bargain.date1.strftime("%d.%m.%Y")}-{bargain.date2.strftime("%d.%m.%Y")}')

        return (title, info)

    def get_orders(self, orders, state = Order_status.All):
        title = "Arrival\t\tOrigin\tDestination\tLoad[kg]\tStatus\tMoney[$]"
        info = []
        for order in orders:
            if order.compare_status(state):
                money = '-' if order.money is None else round(order.money, 1)
                info.append(f'{order.arrival_datetime.strftime("%d.%m.%Y %H:%M")}\t{order.origin}'
                            f'\t{order.destination}\t{order.load}\t{order.status.name}\t{money}')

        return (title, info)

    def form_order(self, company_info, origin=None, destination=None, arrival_date=None,
                   load=1, experience_matters=True, order=None):
        if order is None:
            order = company_info.add_order(origin, destination, arrival_date, load, experience_matters)

        distance, time = company_info.map.get_route_info(order.origin, order.destination)
        delta = order.arrival_datetime - datetime.now() - timedelta(hours=time)
        if delta < timedelta():
            order.cancel_order()
            raise TimeoutError('No enough time')

        car = company_info.get_available_car(order.load)
        driver = company_info.get_available_driver(order.experience_matters)

        driver_payment = 10 * (time + driver.driving_experience)
        gas_payment = car.gas_consumption * distance

        order.money = 1.3 * (gas_payment + driver_payment)
        order.execute_order(driver, car, time)

        return order