#include <cs50.h>
#include <stdio.h>

int askHeight();
void printOuterWhitespace(int outerWhitespaces);
void printBlock(int blocks);

int main(void)
{
    // Get Height
    int height = askHeight();
    // Print blocks
    for (int i = 1; i <= height; i++)
    {
        printOuterWhitespace(height - i);
        printBlock(i);
        printf("\n");
    }
}

// Get height of the pyramid
int askHeight()
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}

// Print white spaces
void printOuterWhitespace(int outerWhitespaces)
{
    for (int i = 0; i < outerWhitespaces; i++)
    {
        printf(" ");
    }
}

// Print bricks
void printBlock(int blocks)
{
    for (int i = 0; i < blocks; i++)
    {
        printf("#");
    }
}

