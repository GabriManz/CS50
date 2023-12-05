from math import floor

def main():
    # Get the input from the user
    while True:
        try:
            card_str = input("Number: ")

            # Check if the input consists only of numeric characters
            if not card_str.isdigit():
                raise ValueError("Invalid input: Please enter only numeric characters.")

            card = int(card_str)  # Convert to integer after verifying it's a valid integer

            count = len(card_str)
            if count >= 13 and count <= 16:
                break
            else:
                print("Invalid input: Card number must have between 13 and 16 digits.")
        except ValueError as e:
            print(e)

    # Assign the brand
    brand = "INVALID"  # Initialize brand as "INVALID" in case no condition matches

    if count == 13:
        if card_str[0] == '4':
            brand = "VISA"

    elif count == 15:
        if card_str[0:2] == '34' or card_str[0:2] == '37':
            brand = "AMEX"

    elif count == 16:
        if card_str[0:2] in ('51', '52', '53', '54', '55'):
            brand = "MASTERCARD"
        elif card_str[0] == '4':
            brand = "VISA"

    # Check if the number of digits is correct before validating Luhn's Algorithm
    if brand != "INVALID":
        last = 0
        tempx = 0
        secToLast = 0

        # Pick odd and even numbers starting from the end and sum them
        while card > 0:
            last += card % 10

            # Eliminate the last digit to access the first even number from the end
            card =  card //10

            tempx = (card % 10) * 2

            # If the even number * 2 is 10 or bigger, take the single digits and add them to the rest of the odds
            if tempx >= 10:
                secToLast += tempx % 10
                tempx //= 10
                secToLast += floor(tempx)

            # If the even number * 2 is 9 or less, just add it to the others
            else:
                secToLast += tempx

            card //= 10

        # If it validates the Algorithm, print the brand
        if (last + secToLast) % 10 == 0:
            print("Brand:", brand)

        else:
            print("INVALID")

    # Print "INVALID" if the digits number was not correct in the first place
    else:
        print("INVALID")

if __name__ == "__main__":
    main()
