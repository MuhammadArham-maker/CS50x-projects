from cs50 import get_string

# Defining main function


def main():

    # Taking input as the cardnumber
    cardnumber = get_string("Number: ")

    # Stores the return value True for valid cardnumber
    valid = checksum(cardnumber)

    # Checks for which type of card
    if len(cardnumber) == 15 and valid and cardnumber.startswith(('34', '37')):
        print("AMEX")

    elif len(cardnumber) == 16 and valid and cardnumber.startswith(('51', '52', '53', '54', '55')):
        print("MASTERCARD")

    elif len(cardnumber) in [13, 16] and valid and cardnumber.startswith('4'):
        print("VISA")

    else:
        print("INVALID")

# Returns True for a valid cardnumber and False for in-valid one


def checksum(cardnumber):
    # Covert to List of Integers
    digits = [int(num) for num in cardnumber]
    total_sum = 0

    # Double every other digit starting from the 2nd-to-last
    for i in range(len(digits) - 2, -1, -2):
        doubled = digits[i] * 2
        total_sum += (doubled // 10) + (doubled % 10)

    # Adding the digits that weren't doubled
    for i in range(len(digits) - 1, -1, -2):
        total_sum += digits[i]

    # Check if valid
    return total_sum % 10 == 0


main()
