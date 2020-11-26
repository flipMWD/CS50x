# Trying 6 digits passwords
for i in range(0, 1000000):
    print(f"Checking {i:06}...")

# Cracking passwords from list of common
with open("pwords") as file:
    for word in file.readlines()
        print(f"Checking {word.rstrip()}...")
