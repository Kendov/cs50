from cs50 import get_int

# check if value is between 1 and 8 and if is decimal number
while True:
    inp = input("Height: ")
    if str.isdecimal(inp) and int(inp) in range(1, 9):
        break

height = int(inp)

# print the blocks
for i in range(1, height + 1):
    print(f"{' ' * (height - i)}{'#' * i}  {'#' * i}")
