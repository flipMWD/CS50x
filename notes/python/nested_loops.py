print("?" * 4)                  # pythonic

for i in range(4):
    print("?", end="")          # by default, opt arg end="\n"

print()

print("#\n" * 3, end="")

for i in range(3):
    for j in range(3):
        print("#", end="")
    print()
