# F-strings are defined by prefixing a string with f or F, allowing variables
# and expressions to be embedded directly within curly braces {},
# which serve as placeholders.
from datetime import datetime
name = "Alice"
age = 25
print(f"My name is {name} and I am {age} years old.")

# Using Expressions in F-Strings
x = 5
y = 3
print(f"The sum of {x} and {y} is {x + y}.")

# Rounding Decimals
pi = 3.14159
print(f"Pi rounded to 2 decimal places: {pi:.2f}")

# Displaying Large Numbers with Commas
salary = 1000000
print(f"Annual salary: ${salary:,}")

# Displaying Percentages
progress = 0.85

# Working with Dates and Time
today = datetime.now()
print(f"Today's date: {today:%Y-%m-%d}")

# Multiline F-Strings
name = "Alice"
age = 25
bio = f"""
Name: {name}
Age: {age}
Status: Active
"""
print(bio)

# Using F-Strings with Dictionaries
person = {"name": "Alice", "age": 25}
print(f"{person['name']} is {person['age']} years old.")
