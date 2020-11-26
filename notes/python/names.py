from sys import exit

names = ["Michael", "Dwight", "Pam", "Jim"]

if "Pam" in names:
    print("Found")
    exit(0)

print("Not found")
exit(1)
