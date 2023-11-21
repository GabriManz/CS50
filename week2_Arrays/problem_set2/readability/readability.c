#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float calculate_colemanLaiuIndex(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    if (text[0] == '\0') {
        printf("No text input.\n");
        return 1;
    }

    int letters = count_letters(text);
    printf("%i Letters\n", letters);

    int words = count_words(text);
    printf("%i Words\n", words);

    int sentences = count_sentences(text);
    printf("%i Sentences\n", sentences);

    int colemanLaiuIndex = calculate_colemanLaiuIndex(letters, words, sentences);

    if (colemanLaiuIndex > 16)
    {
        printf("Grade 16+\n");
    }
    else if (colemanLaiuIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", colemanLaiuIndex);
    }
}

// Letter Count
int count_letters(string text)
{
    int counter = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalnum(text[i]))
        {
            counter++;
        }
    }
    return counter;
}

// Words Count
int count_words(string text)
{
    int counter = 0;
    int i = 0;

    while (text[i] != '\0')
    {
        if (isalnum(text[i]))
        {
            counter++;
            while (isalnum(text[i]) && text[i] != '\0')
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }

    return counter;
}

// Sentence Count
int count_sentences(string text)
{
    int counter = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            counter++;
        }
    }
    return counter;
}

// Coleman-Liau Index
float calculate_colemanLaiuIndex(int letters, int words, int sentences)
{
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;
    return round(0.0588 * L - 0.296 * S - 15.8);
}
