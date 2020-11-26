x = 1
y = 2

print(f"x is {x}, is {y}")

x, y = y, x         # equiv to swap(a, b){int t=a; a=b; b=t;}

print(f"x is {x}, is {y}")

a = "Alpha"
b = "Beta"
c = "Gamma"

print(f"a = {a}\nb = {b}\nc = {c}")

a, b, c = b, c, a

print(f"a = {a}\nb = {b}\nc = {c}")
