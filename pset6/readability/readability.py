import re

inp = input("Text: ")

words = len(inp.strip())

letters = 0
# Get amount of letters
for char in inp:
    if str.isalpha(char):
        letters += 1

# Get amount of words
words = len(inp.split())

# Get amount of sentences
sentences = len(re.split('\. |\! |\? ', inp))


index = 0.0588 * (letters/words*100) - 0.296 * (sentences/words*100) - 15.8

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(index)}")