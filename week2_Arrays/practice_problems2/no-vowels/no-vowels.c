// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string replace(string input);

int main(int argc, string argv[])
{
    string text;
    // Print on command line & usage message if no args
    if (argc < 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    // loop through each input argument and call 'replace'
    for (int i = 1; i < argc; i++)
    {
        // Replace vowels in current argument and print result
        string result = replace(argv[i]);
        printf("%s", result);

        // If not last argument (aka word), add space to separate words
        if (i != argc - 1)
        {
            printf(" ");
        }
    }
    // Add newline at end of output
    printf("\n");
    return 0;
}

string replace(string input)
{
    // Allocate memory for ouput; same as input
    string output = input;

    // Keep looping through input until it equals same length
    for (int i = 0; i < strlen(input); i++)
    {
        {
            char c = tolower(input[i]);
            // Use switch statement to switch vowels
            switch (c)
            {
                case 'a':
                    output[i] = '6';
                    break;

                case 'e':
                    output[i] = '3';
                    break;

                case 'i':
                    output[i] = '1';
                    break;

                case 'o':
                    output[i] = '0';
                    break;

                default:
                    output[i] = input[i];
                    break;
            }
        }
    }
    return output;
}
