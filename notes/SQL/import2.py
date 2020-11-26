import cs50
import csv

open("shows2.db", "w").close()
db = cs50.SQL("sqlite:///shows2.db")

db.execute("CREATE TABLE shows (tconst TEXT, primaryTitle TEXT, startYear NUMERIC, genres TEXT)")

with open("shows1.csv") as titles:
    reader = csv.DictReader(titles)

    for row in reader:
        tconst = row["tconst"]
        primaryTitle = row["primaryTitle"]
        startYear = row["startYear"]
        genres = row["genres"]

        db.execute("INSERT INTO shows (tconst, primaryTitle, startYear, genres) VALUES(?, ?, ?, ?)", tconst, primaryTitle, startYear, genres)
