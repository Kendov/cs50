
#check the input
while True:
    credit_card = input("Number: ")
    if (str.isdecimal(credit_card)):
        break


digits = ""
# Multiply every other digit by 2, starting with the number’s second-to-last digit
for i in range(len(credit_card) -2, -1, -2):
    digits += str(int(credit_card[i]) * 2)
#add products’ digits together
total = sum(int(number) for number in digits)

#sum total with digits that weren’t multiplied by 2
for i in range(len(credit_card) -1, -1, -2):
    total += int(credit_card[i])



if str(total)[len(str(total)) - 1] != '0':
    print("INVALID")
elif credit_card[:2] in ('34', '37') and len(str(credit_card)) == 15:
    print("AMEX")
elif int(credit_card[:2]) in range(51, 56) and len(str(credit_card)) == 16:
    print("MASTERCARD")
elif len(str(credit_card)) in (13, 16) and credit_card[0] == '4' :
    print("VISA")

