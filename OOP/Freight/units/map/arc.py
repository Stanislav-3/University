

class Arc:
    def __init__(self, distance, max_speed = 90):
        if float(distance) > 10000:
            raise Exception('Distance is too large. Should be <= 10000 km')

        if float(max_speed) > 210:
            raise Exception('Max speed is too large. Should be <= 210 hm/h')

        self.distance = round(float(distance), 2)
        self.max_speed = round(float(max_speed), 2)

