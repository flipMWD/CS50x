import cs50
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python roster.py House")

db = cs50.SQL("sqlite:///students.db")
rows = db.execute(
    "SELECT first, middle, last, birth\
    FROM students\
    WHERE house = ?\
    ORDER BY last ASC, first ASC",
    argv[1].capitalize())

for row in rows:
    name = " ".join(filter(None, [row["first"], row["middle"], row["last"]]))
    print(name + ", born " + str(row["birth"]))