

class Driver():
    def __init__(self, name: str, middle_name: str, surname: str, driving_experience):
        try:
            name_len = len(name)
            middle_name_len = len(middle_name)
            surname_len = len(surname)
        except:
            raise Exception('Invalid naming format. Names should be a string')
        if name_len >= 15 or middle_name_len >= 15 or surname_len >= 15:
            raise Exception('Naming is too large. Should be < 15 symbols')

        try:
            driving_experience = round(float(driving_experience), 2)
        except:
            raise Exception('Wrong driving experience format! Should be a float value')
        if  driving_experience > 40:
            raise Exception('Driving experience is too large. Should be <= 40')

        self.name = name
        self.middle_name = middle_name
        self.surname = surname
        self.driving_experience = driving_experience
        self.is_available = True