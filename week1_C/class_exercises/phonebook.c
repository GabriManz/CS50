#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string first = get_string("What is your first name? ");
    string last = get_string("What is your last name? ");
    string address = get_string("What is your address? ");
    int age = get_int("What is age? ");
    long number = get_long("What is your phone number? ");
    printf("Name: %s %s\nAddress: %s\nAge: %i\nNumber: %li\n", first, last, address, age, number);
}
