// Incorrectly gets a string from user using scanf

#include <stdio.h>

int main(void)
{
    char *s = NULL;
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
}
