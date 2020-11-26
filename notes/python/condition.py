s = input("Do you agree? ")

if s == "Y" or s == "y":                        # logical operator
    print("Agreed.")
elif s.lower() in ["n", "no", "nope"]:          # list of possible inputs
    print("Not agreed.")
