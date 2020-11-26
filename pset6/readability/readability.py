from cs50 import get_string

t = get_string("Text: ")

l = w = s = 0

in_word = False
for c in t:
    if c.isalpha():
        l += 1
        if not in_word:
            in_word = True
    elif c in ['.', '!', '?']:
        s += 1
        if in_word:
            w += 1
            in_word = False
    elif c in [" ", "\""] and in_word:
        w += 1
        in_word = False

# print(f"L: {l}, W: {w}, S: {s}")

l_avg = l / w * 100
s_avg = s / w * 100

# Coleman-Liau Index
cli = (0.0588 * l_avg) - (0.296 * s_avg) - 15.8

if cli < 1:
    print("Before Grade 1")
elif cli >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(cli)}")