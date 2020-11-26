import csv

phone = open("phonebook.csv", "a")

name = input("Name: ")
number = input("Number: ")

writer = csv.writer(phone)
writer.writerow((name, number))     # passing a tuple to lib func

phone.close()

#-[ Alternate Syntax ]-#

with open("grocery-list.csv", "a") as buy_list:
    writing_head = csv.writer(buy_list)
    while True:
        item = input("Item: ")
        qnty = input("Quantity: ")
        writing_head.writerow((item, qnty))
