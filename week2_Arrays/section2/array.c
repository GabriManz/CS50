#include <stdio.h>
#include <cs50.h>

int main (void)
{
    //Get the legth
    int length;
    do
    {
    length = get_int("Lenght: ");
    }
    while (length < 1);

    //Declare our array
    int twice[length];

    //Set the first value
    twice[0] = 1;
    printf("%i\n", twice[0]);

    //Make the current element twice the previous
    for(int i = 1; i < length; i++)
    {
        twice[i] = twice[i - 1] * 2;

        //Print the array
        printf("%i\n", twice[i]);
    }
}
