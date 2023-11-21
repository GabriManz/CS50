#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long card_number_input;
    do {
        card_number_input = get_long_long("Number: ");
    } while (card_number_input <= 0);

    int total_digits = 0;
    long long card_number_temp = card_number_input;

    while (card_number_temp != 0) {
        card_number_temp /= 10;
        total_digits++;
    }

    if (total_digits < 13 || total_digits > 16) {
        printf("INVALID\n");
        return 0;
    }

    int card_number[total_digits];
    card_number_temp = card_number_input;

    for (int i = total_digits - 1; i >= 0; i--) {
        card_number[i] = card_number_temp % 10;
        card_number_temp /= 10;
    }

    int sum_of_numbers = 0;
    for (int i = 0; i < total_digits; i++) {
        if (i % 2 == total_digits % 2) { // Check if it's in a position to double
            int temp = card_number[i] * 2;
            if (temp >= 10) {
                sum_of_numbers += temp % 10;
                sum_of_numbers += temp / 10;
            } else {
                sum_of_numbers += temp;
            }
        } else {
            sum_of_numbers += card_number[i];
        }
    }

    if (sum_of_numbers % 10 != 0) {
        printf("INVALID: Credit card number is not valid.\n");
        return 0; // Exit here since it's invalid
    }

    // Check the first digits for validity after validation
    if (total_digits >= 1 && card_number[0] == 4) {
        printf("VISA\n");
    } else if (total_digits >= 2 && card_number[0] == 3 && (card_number[1] == 4 || card_number[1] == 7)) {
        printf("AMEX\n");
    } else if (total_digits >= 2 && card_number[0] == 5 && (card_number[1] >= 1 && card_number[1] <= 5)) {
        printf("MASTERCARD\n");
    } else {
        printf("INVALID: Credit card number is not recognized.\n");
    }

    return 0;
}



