from cs50 import get_int

n = 0
while n < 1 or n > 8:
    n = get_int("Height: ")

gap = 2
for i in range(n):
    for j in range(n + gap + (i + 1)):
        if (j < n and j >= n - (i + 1)) or j >= (n + gap):
            print("#", end="")
        else:
            print(" ", end="")
    print()