import cs50
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python import.py file.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

with open(argv[1]) as characters:
    reader = csv.DictReader(characters)

    for row in reader:
        name  = row["name"].split(" ")
        first = name[0]
        last  = name[-1]
        if len(name) > 2:
            middle = " ".join(name[1:-1])
        else:
            middle = None
        house = row["house"]
        birth = row["birth"]

        db.execute(
            "INSERT INTO students (first, middle, last, house, birth)\
            VALUES (?, ?, ?, ?, ?)",
            first, middle, last, house, birth)