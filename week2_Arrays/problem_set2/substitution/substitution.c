#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

void encipher(string plaintext, string key);

int main(int argc, string argv[])
{
//Get the key
    string key = argv[1];

//Validate the Key
    // Check that a proper command line argument was entered
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check that the key has 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Check that the key contains only unique alphabetic characters
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetic characters\n");
            return 1;
        }
        for (int j = i + 1; j < 26; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain duplicate characters\n");
                return 1;
            }
        }
    }

//Get plaintext
    string plaintext = get_string("Plaintext: ");

//Encipher
    encipher(plaintext, key);

//Print ciphertext
    printf("Ciphertext: %s\n", plaintext);
}

//Substitution key into plaintext to obtain ciphertext
void encipher(string plaintext, string key)
{
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (isupper(plaintext[i]))
        {
            int index = plaintext[i] - 'A'; // Convert to 0-based index
            plaintext[i] = toupper(key[index]); // Use the key for substitution
        }
        else if (islower(plaintext[i]))
        {
            int index = plaintext[i] - 'a'; // Convert to 0-based index
            plaintext[i] = tolower(key[index]); // Use the key for substitution
        }
    }
}
