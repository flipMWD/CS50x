from sys import argv, exit
import csv
import re

if len(argv) != 3:
    print("DNA requires database and sequence to be analysed.")
    exit(1)

with open(argv[1]) as db_file, open(argv[2]) as sq_file:
    db = list(csv.reader(db_file))
    sq = sq_file.read()

# Create regex patterns to match consecutive occurrences
STRs = list()
re_p = "(?:"
re_s = ")+"
re_l = len(re_p) + len(re_s)        # calc extra characters for diff later
for STR in db[0][1:]:
    STRs.append(re_p + STR + re_s)  # (?:ATCG)+

# Count the pattern length of the longest chain for each
count = list()
for pat in STRs:
    long_chain = 0
    STR_l = len(pat) - re_l         # calc original STR length
    sq_match = re.findall(pat, sq)
    for chain in sq_match:
        # Turn length of characters into length of "words"
        links = round(len(chain) / STR_l)
        if links > long_chain:
            long_chain = links
    count.append(long_chain)

# Compare count with database
count_l = len(count)
for profile in db[1:]:
    m = 0
    for col in range(len(profile[1:])):
        if int(profile[col+1]) == count[col]:
            m += 1
            if m >= count_l:
                print(profile[0])
                exit(0)
        else:
            break

print("No match")
exit(1)
