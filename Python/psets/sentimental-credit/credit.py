import re


def main():
    # Receive input from the user
    card_number = input("Number: ")

    # Check if the card matches start and length of amex
    amex = re.search("^34|^37", card_number)
    if amex != None and len(card_number) == 15:
        if formula(card_number):
            print("AMEX")

    # Check if the card matches start and length of mastercard
    mastercard = re.search("^5", card_number)
    if mastercard != None and len(card_number) == 16:
        if formula(card_number):
            print("MASTERCARD")

    # Check if the card matches start and length of visa
    visa = re.search("^4", card_number)
    if visa != None and (len(card_number) == 13 or 16):
        if formula(card_number):
            print("VISA")

    # If none of the checks pass print INVALID
    else:
        print("INVALID")


# Luhn's algorithm
def formula(card_number):
    sum1 = 0
    sum2 = 0
    # Start a loop at the end of the card number and count back one digit at a time
    for i in range(len(card_number), len(card_number), -1):
        # Every even digit multiply by 2
        if i % 2 == 0:
            current = card_number[i] * 2
            if len(current > 1):
                # Add digits together then add to sum
                sum1 = current[0] + current[1]
        # Every odd digit add to sum
        if i % 2 != 0:
            sum2 += card_number[i]
    # Total the sums
    sum = sum1 + sum2
    # If the last digit is 0 the the checksum is passed
    if sum % 10 == 0:
        return True


if __name__ == "__main__":
    main()