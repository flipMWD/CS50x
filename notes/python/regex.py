import re

s = input("Do you agree? ")

if re.search("^y(es)?$", s, re.IGNORECASE):
    print("Agreed.")
elif re.search("^n(o|ope)?$", s, re.IGNORECASE):
    print("Not agreed.")

names = input("What's your name? ")
matches = re.search("(?:M|m)y name is (.*)", names)     # non-capture group

if matches:
    print(f"Hey, {matches[1]}.")
else:
    print("Hey, you.")
