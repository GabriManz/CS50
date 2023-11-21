// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_number = false;
    bool has_symbol = false;

    for (int i = 0; password[i] != '\0'; i++)
    {
        char c = password[i];

        if (islower(c))
        {
            has_lowercase = true;
        }
        else if (isupper(c))
        {
            has_uppercase = true;
        }
        else if (isdigit(c))
        {
            has_number = true;
        }
        else if (!isalnum(c)) //!isalnum Means that you are looking for a non alpha-numeric character
        {
            has_symbol = true;
        }

        // If all criteria are met, no need to continue checking
        if (has_lowercase && has_uppercase && has_number && has_symbol)
        {
            return true;
        }
    }

    return false;
}
