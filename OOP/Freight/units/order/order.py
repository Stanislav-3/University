from datetime import datetime, timedelta
from units.order.order_status import Order_status as status


class Order():
    def __init__(self, origin, destination, arrival_datetime, load, experience_matters):
        try:
            if arrival_datetime.find(' ') > 0:
                date, time = arrival_datetime.split(' ')
            else:
                date, time = arrival_datetime, ' '
            date = date.split('.')
            time = time.split(':')
            args = [*map(int, date[::-1])]
            if len(time) > 1:
                time = [*map(int, time)]
                args.extend(time)
            self.arrival_datetime = datetime(*args)
            if self.arrival_datetime < datetime.now():
                raise TimeoutError("Wrong arrival datetime format...\n"
                                   "Arrival datetime cannot be in the past :)")
        except TimeoutError:
            raise
        except Exception as e:
            raise Exception("Wrong arrival datetime format...\n"
                            "Correct is dd.mm.yy hh:mm:ss")

        try:
            self.load = round(float(load), 2)
            if self.load >= 30:
                raise Exception
        except Exception as e:
            raise Exception("Invalid load format. Should be float value < 30")

        try:
            if len(origin) >= 15 or len(destination) >= 15:
                raise Exception
            self.origin = origin
            self.destination = destination
        except:
            raise Exception('Invalid city naming. Names should be < 15 symbols')

        self.status = status.Reserved
        self.experience_matters = experience_matters
        self.money = None
        self.car = None
        self.driver = None

    def __setattr__(self, key, value):
        if key == "money" and value is not None:
            try:
                value = round(float(value), 2)
                if value > 1000000:
                    raise Exception
            except:
                raise Exception("Invalid money format. Should be float < 15")
            super(Order, self).__setattr__(key, value)
        else:
            super(Order, self).__setattr__(key, value)

    def compare_status(self, stat: status):
        if stat == status.All:
            return True
        else:
            return stat == self.status

    def cancel_order(self):
        self.status = status.Canceled

        if self.car is not None:
            self.car.is_available = True
        self.car = None

        if self.driver is not None:
            self.driver.is_available = False
        self.driver = None

    def execute_order(self, driver, car, time):
        self.status = status.Executing

        car.is_available = False
        self.car = car

        driver.is_available = False
        self.driver = driver

        self.arrival_datetime = datetime.now() + timedelta(hours=time)

    def complete_order(self):
        self.status = status.Completed

        self.car.is_available = True
        self.car = None

        self.driver.is_available = True
        self.driver = None