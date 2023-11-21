#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompting the user for a starting # of llamas
    int start;
    do
    {
        start = get_int("Start Size: ");
    }
    while (start < 9);

    // Prompting the user for an ending # of llamas
    int end;
    do
    {
        end = get_int("End Size: ");
    }
    while (end < start);

    // How many years will it take to get the goal?
    int years = 0;
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }
    printf("Years: %d\n", years);
}
