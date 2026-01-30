import ElectricCar
from Car import Battery

tesla = ElectricCar('tesla', 'model_x', 2018, Battery(90, 2020))


tesla.describe()
