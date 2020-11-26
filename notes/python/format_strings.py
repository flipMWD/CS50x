import random

# Underscores in numbers have no effect in code
rnum = random.randint(1_000, 1_000_000_000)

# f-Strings can be formated by thousands with commas
print(f"Random Number: {rnum:,}")
# Numbers: {value:(pad_fill)(width).(precision)f[ixed point]}
print(f"Numbers: {78:04} {12.5:5} {0.78945:.2f}")

name = "Eric"
age = 74
print(f"Hello, {name}. You are {age}.")
print(f"{2 * 37}")

def to_lowercase(input):
    return input.lower()

print(f"{to_lowercase(name)} is funny.")

class Comedian:
    def __init__(self, first_name, last_name, age):
        self.first_name = first_name
        self.last_name = last_name
        self.age = age

    def __str__(self):
        return f"{self.first_name} {self.last_name} is {self.age}."

    def __repr__(self):
        return f"{self.first_name} {self.last_name} is {self.age}. Surprise!"

new_comedian = Comedian("Eric", "Idle", "74")
print(f"{new_comedian}")        # default use
print(f"{new_comedian!r}")      # conversion flag

profession = "Comedian"
message = f"Hello, {name}. "\
          f"You are a {profession}."
print(message)

affiliation = "Monty Python"
textblock = f"""
    Hello, {name} {new_comedian.last_name}.
    Your were in {affiliation}!
"""
print(textblock)

print(f"{{Braces}} and math {{{3 * 12}}}")
print(f"Can't use backslashes inside {{\"expression like this\"}}")
