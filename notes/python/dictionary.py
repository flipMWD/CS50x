from sys import exit

# Associative Array - Dictionary
people = {
    "Michael": "615-846-0444",
    "Dwight": "854-645-4021",
    "Pam": "230-849-0020",
    "Jim": "231-283-4881",
}

if "Dwight" in people:                  # python iterates on it's own
    print(f"Found {people['Dwight']}")  # dict[ID] equivalent to arr[i]
    exit(0)

exit(1)
