// Prints command-line arguments

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
}
