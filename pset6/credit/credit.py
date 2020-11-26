from cs50 import get_string


class Brands:
    def __init__(self, brand, length, start):
        self.b = brand
        self.l = length
        self.s = start


amex = Brands("AMEX", (15,), (34, 37))
macd = Brands("MASTERCARD", (16,), (51, 52, 53, 54, 55))
visa = Brands("VISA", (13, 16), (4,))
invd = "INVALID"

b_flg = [amex, macd, visa]

valid = False
while not valid:
    num = get_string("Number: ")
    if num.isdigit():
        valid = True

dig = list()
rmd = list()
i = 0
for x in reversed(num):
    i += 1
    if i % 2 == 0:
        ones = int(x) * 2
        if ones > 9:
            tens = int(ones / 10)
            ones %= 10
            dig.append(tens)
        dig.append(ones)
    else:
        rmd.append(int(x))

d_sum = sum(dig) + sum(rmd)
n_len = len(num)

if d_sum % 10 == 0:
    for b in range(len(b_flg)):
        for l in b_flg[b].l:
            if n_len == l:
                for s in b_flg[b].s:
                    if s == int(num[0] + num[1]) or s == int(num[0]):
                        print(b_flg[b].b)
                        exit(0)

print(invd)
exit(1)