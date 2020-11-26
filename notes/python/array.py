scores = []
scores.append(42)
scores.append(43)
scores.append(73)
print(f"Average: {sum(scores)/len(scores)}")

scores2 = [22, 23, 64]
print(f"Average: {sum(scores2)/len(scores2)}")

string = input("Input: ")
print("Output: ", end="")
for i in range(len(string)):    # counting str lenght
    print(f"{string[i]}{i + 1} ", end="")

print("(", end="")
for c in string:                # python can iterate on a str by itself
    print(c, end="");
print(")")

print("Uppercase:", string.upper())
