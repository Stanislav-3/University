

class Car():
    def __init__(self, model, gas_consumption, max_load):
        try:
            model_len = len(model)
        except:
            raise Exception('Invalid model format. Model should be a string')
        if model_len >= 15:
            raise Exception('Model name is too large. Should be < 15 symbols')

        try:
            gas_consumption = round(float(gas_consumption), 2)
        except:
            raise Exception('Wrong gas consumption format! Should be a float value')
        if gas_consumption >= 30:
            raise Exception('Gas consumption is too large. Should be < 30 symbols')

        try:
            max_load = round(float(max_load), 2)
        except:
            raise Exception('Wrong gas consumption format! Should be a float value')
        if max_load >= 30:
            raise Exception('Max load is too large. Should be < 30 symbols')

        self.model = model
        self.gas_consumption = gas_consumption
        self.max_load = max_load
        self.is_available = True
    