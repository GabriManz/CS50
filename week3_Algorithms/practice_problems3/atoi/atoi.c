#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Base case: an empty string, return 0
    if (input[0] == '\0')
    {
        return 0;
    }

    // Get the index of the last character in the string
    int last_index = strlen(input) - 1;

    // Convert the last character to its numeric value (based on ASCII)
    int numeric_value = input[last_index] - '0';

    // Shorten the string by removing the last character
    input[last_index] = '\0';

    // Recursive call to convert the shortened string to an integer
    int result = convert(input);

    // Return the calculated value plus 10 times the numeric value of the last character
    return result * 10 + numeric_value;
}
