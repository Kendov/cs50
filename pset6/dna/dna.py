import csv
import re
from sys import argv, exit

# check the arguments
if len(argv) != 3:
    print(len(argv))
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

csvfile = open(argv[1], 'r')
with open(argv[2], 'r') as file:
    sequence = file.read()

database = csv.reader(csvfile)


# get the str from header and remove the name field
dna_str = csv.DictReader(csvfile).fieldnames
dna_str.pop(0)


# get amount of matches on each STR
str_amount = {}
for key in dna_str:
    biggest_sequence = 0
    current_sequence = 0
    index = 0
    key_size = len(key)
    while index < len(sequence):
        # if find one match start counting
        test = sequence[index:index + key_size]
        if sequence[index:index + key_size] == key:
            current_sequence += 1
            index += key_size
            if current_sequence > biggest_sequence:
                biggest_sequence = current_sequence
            continue
        elif current_sequence > 0:
            current_sequence = 0
            continue
        index += 1
    str_amount[key] = biggest_sequence


# convert database in to dictionary
database_dictionary = []
for row in database:
    database_dictionary.append({row[0]: row[1:]})

# compare values
for person in database_dictionary:
    person_values = list(person.values())
    person_values = [int(i) for i in person_values[0]]
    if person_values == list(str_amount.values()):
        print(list(person.keys())[0])
        exit(0)

print("No match")