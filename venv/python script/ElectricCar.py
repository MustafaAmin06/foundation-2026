from Car import Car

class ElectricCar(Car):
    def __init__(self, make, model, year, battery_model):
        super().__init__(make, model, year)
        self.battery_model = battery_model
    
    def describe(self):
        print(f"This car has a {self.battery_model.battery_size} kWh battery and was made to last until {self.battery_model.expiry}\n")
        print(f"This car is made by {self.make}, made in {self.year}, and is the model: {self.model}. The odometer is {self.odometer}")

