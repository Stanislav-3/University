from datetime import datetime


class Budget:
    def __init__(self, income, date1, date2=datetime.now()):
        try:
            self.income = round(income, 2)
        except:
            raise Exception('Invalid income format')

        if not isinstance(date1, datetime) or not isinstance(date2, datetime):
            raise Exception('Invalid datetime format')
        self.date1 = date1
        self.date2 = date2
