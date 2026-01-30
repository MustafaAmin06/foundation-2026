class Car:
    def __init__(self, make, model, year):
        self.make = make
        self.model = model
        self.year = year
        self.odometer = 0

    def get_info(self):
        print(f"Your car is a {self.year} {self.make} {self.model}")

    def get_milate(self, x):
        self.year += x

class Battery:
    def __init__(self, battery_size, expiry):
        self.battery_size = battery_size
        self.expiry = expiry

    def get_battery_info(self):
        print(f"{self.battery_size} {self.expiry}")
