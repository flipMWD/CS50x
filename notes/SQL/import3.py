import cs50
import csv

open("shows3.db", "w").close()
db = cs50.SQL("sqlite:///shows3.db")

db.execute("CREATE TABLE shows (id INT, title TEXT, year NUMERIC, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INT, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id))")

with open("title.basics.tsv") as db_file:
    reader = csv.DictReader(db_file, delimiter="\t")

    for row in reader:
        if row["titleType"] == "tvSeries":
            if row["startYear"] == "\\N":
                continue
            startYear = int(row["startYear"])
            if startYear < 1970:
                continue
            tconst = int(row["tconst"][2:])
            primaryTitle  = row["primaryTitle"]
            db.execute("INSERT INTO shows (id, title, year) VALUES(?, ?, ?)", tconst, primaryTitle, startYear)

            genres = row["genres"]
            if genres == "\\N":
                continue
            for genre in genres.split(","):
                db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?)", tconst, genre)
