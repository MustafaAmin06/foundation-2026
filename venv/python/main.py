import json

numbers = [nums for nums in range(1,11)]

with open('stuff.json', 'w') as f:
    json.dump(numbers, f)