import csv

with open("title.basics.tsv") as titles:
    reader = csv.DictReader(titles, delimiter="\t")

    with open("shows1.csv", "w") as shows:
        writer = csv.writer(shows)
        writer.writerow(["tconst", "primaryTitle", "startYear", "genres"])

        for row in reader:
            if row["startYear"] == "\\N":
                continue
            year = int(row["startYear"])
            if year < 1980:
                continue
            if row["titleType"] == "tvSeries":
                writer.writerow([\
                    row["tconst"],\
                    row["primaryTitle"],\
                    row["startYear"],\
                    row["genres"]])
