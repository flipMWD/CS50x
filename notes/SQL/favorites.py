import csv

counts = {}

with open("movies.csv") as bp:
    db = csv.DictReader(bp)

    for row in db:
        title = row["title"].lower()
        if title in counts:
            counts[title] += 1
        else:
            counts[title] = 1

# Anonymous Function = lambda arg: return
for title, count in sorted(counts.items(), key=lambda item: item[1], reverse=True):
    print(title, count, sep=" | ")
