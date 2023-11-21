#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Check that a proper command line argument was entered
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Get plaintext string from the user
    string s = get_string("Plaintext: ");

    // Convert argv into an int
    int key = atoi(argv[1]);
    printf("Ciphertext: ");

    // Iterate through the string and output ciphertext
    for (int i = 0; i < strlen(s); i++)
    {
        int cipherkey = key % 26;

        // Check to see if the character is a letter
        if (!isalpha(s[i]))
        {
            printf("%c", s[i]);
        }
        // Output if the character is a letter and doesn't need to wrap around
        else if (isupper(s[i]) && s[i] + cipherkey <= 'Z')
        {
            printf("%c", s[i] + cipherkey);
        }
        else if (islower(s[i]) && s[i] + cipherkey <= 'z')
        {
            printf("%c", s[i] + cipherkey);
        }
        // Output if the character is a letter and needs to wrap around
        else
        {
            printf("%c", s[i] + cipherkey - 26);
        }
    }
    printf("\n");
    return 0;
}
