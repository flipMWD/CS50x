from time import sleep

i = 1

while True:
    print(i)
    sleep(.01)          # fractions of second
    i *= 2              # int has no upperboud
