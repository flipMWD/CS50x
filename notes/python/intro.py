print("Hello World!")

cat = "concatenation"
print("Can use + for " + cat + ".")

print("Can receive", "multiple args", "adding [spaces]", "in between.")

in_word = "interpolation"
print(f"Format string with {in_word} wordue")

int_counter = 0
int_counter = int_counter + 1
int_counter += 1
print("Counter value = ", int_counter)

x = 5
y = x ** 2      # comment, ** equivalent to x^2 or pow(x, 2)
if x < y:
    print(f"x({x}) is less than y({y}).")
elif x > y:
    print(f"x({x}) is greater than y({y}).")
else:
    print(f"x({x}) is equal to y({y}).")

print("cough\n" * 3)            # multiply str by int

i = x - 1
while True and i > 0:           # boolean values are capitalized,
    print("Cool.")              # logical operator &&
    i -= 1

for val in [0, 1, 2]:           # list
    print("Test", (val + 1));   # concat + wouldn't work with str + int

for num in range(10):           # no need for i=0;i>cap;++i
    print(f"Counting... {num}");

# Types
print("\nThese are the implicit types in python:")
print("bool, float, int, str, ...")
# More datatypes
print("\nComplex datatypes:")
print("range\tsequence of numbers")
print("list\tsequence of mutable values")
print("tuple\tsequence of immutable values")
print("dict\tcollection of keyvalue pairs")
print("set\tcollection of unique values\n...")
