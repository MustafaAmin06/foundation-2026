import json
from pathlib import Path

# ============================================
# 1. BASIC JSON READING
# ============================================

# Read entire JSON file into Python object
with open('data.json', 'r') as file:
    data = json.load(file)  # Converts JSON to dict/list
    print(data)

# ============================================
# 2. READ JSON STRING (from variable/API)
# ============================================

json_string = '{"name": "Alice", "age": 30}'
data = json.loads(json_string)  # loads = load string
print(data['name'])  # Access like a dictionary

# ============================================
# 3. SAFE FILE READING (with error handling)
# ============================================

try:
    with open('data.json', 'r') as file:
        data = json.load(file)
except FileNotFoundError:
    print("File not found!")
except json.JSONDecodeError:
    print("Invalid JSON format!")

# ============================================
# 4. READ JSON WITH PATH (works from any directory)
# ============================================

from pathlib import Path

json_path = Path(__file__).parent / "data.json"
with json_path.open('r') as file:
    data = json.load(file)

# ============================================
# 5. READ SPECIFIC KEYS
# ============================================

with open('data.json', 'r') as file:
    data = json.load(file)
    
    # Safe access with .get() - returns None if key missing
    name = data.get('name')
    age = data.get('age', 0)  # Default value if missing
    
    # Direct access (raises KeyError if missing)
    name = data['name']

# ============================================
# 6. READ NESTED JSON
# ============================================

# Example JSON: {"user": {"name": "Bob", "address": {"city": "NYC"}}}
with open('nested.json', 'r') as file:
    data = json.load(file)
    
    # Access nested data
    city = data['user']['address']['city']
    
    # Safe nested access
    city = data.get('user', {}).get('address', {}).get('city', 'Unknown')

# ============================================
# 7. READ JSON ARRAY
# ============================================

# Example JSON: [{"id": 1}, {"id": 2}, {"id": 3}]
with open('array.json', 'r') as file:
    items = json.load(file)  # Returns a list
    
    for item in items:
        print(item['id'])

# ============================================
# 9. READ JSON WITH CUSTOM ENCODING
# ============================================

# For non-UTF-8 files
with open('data.json', 'r', encoding='utf-8') as file:
    data = json.load(file)


# ============================================
# 12. READ MULTIPLE JSON FILES
# ============================================

import glob

# Read all JSON files in a directory
all_data = []
for json_file in glob.glob('*.json'):
    with open(json_file, 'r') as file:
        all_data.append(json.load(file))

# ============================================
# 13. READ JSON WITH CUSTOM DECODER
# ============================================

from datetime import datetime

def custom_decoder(dct):
    # Convert date strings to datetime objects
    if 'date' in dct:
        dct['date'] = datetime.fromisoformat(dct['date'])
    return dct

with open('data.json', 'r') as file:
    data = json.load(file, object_hook=custom_decoder)

# ============================================
# 14. READ JSONL (JSON Lines - one JSON per line)
# ============================================

# Each line is a separate JSON object
with open('data.jsonl', 'r') as file:
    for line in file:
        data = json.loads(line)
        print(data)

# ============================================
# 15. COMPLETE EXAMPLE WITH ALL FEATURES
# ============================================

def read_json_safely(filepath, encoding='utf-8'):
    """
    Safely read JSON file with comprehensive error handling.
    
    Args:
        filepath: Path to JSON file
        encoding: File encoding (default: utf-8)
    
    Returns:
        Parsed JSON data or None if error
    """
    try:
        path = Path(filepath)
        
        # Check if file exists
        if not path.exists():
            print(f"Error: {filepath} not found")
            return None
        
        # Check if file is empty
        if path.stat().st_size == 0:
            print(f"Error: {filepath} is empty")
            return None
        
        # Read and parse JSON
        with path.open('r', encoding=encoding) as file:
            data = json.load(file)
            
        print(f"Successfully loaded {filepath}")
        return data
        
    except json.JSONDecodeError as e:
        print(f"Invalid JSON in {filepath}: {e}")
        return None
    except PermissionError:
        print(f"Permission denied: {filepath}")
        return None
    except Exception as e:
        print(f"Unexpected error: {e}")
        return None

# Usage
data = read_json_safely('data.json')
if data:
    print(json.dumps(data, indent=2))