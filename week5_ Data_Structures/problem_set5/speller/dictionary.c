// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose the number of buckets in the hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Converting a string to lowercase
    int word_length = strlen(word);
    char lowercase[word_length + 1]; // +1 for the null character

    for (int i = 0; i < word_length; i++)
    {
        lowercase[i] = tolower(word[i]);
    }

    lowercase[word_length] = '\0';

    // Hash the lowercase word to find the bucket
    int hash_value = hash(lowercase);

    // Set cursor to appropriate linked list
    node *cursor = table[hash_value];

    // Compare the lowercase word with words in the linked list
    while (cursor != NULL)
    {
        if (strcasecmp(lowercase, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improved hash function using djb2 algorithm
    unsigned int hash = 5381;
    int c;

    while ((c = *word++) != '\0')
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *dictionary_file = fopen(dictionary, "r");

    if (dictionary_file == NULL)
    {
        return false;
    }

    // Read the dictionary and store in the hash table
    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        node *word_node = malloc(sizeof(node));

        if (word_node == NULL)
        {
            unload();
            fclose(dictionary_file);
            return false;
        }

        // Copy the word to the node of the new element
        strcpy(word_node->word, word);

        // Get the hash index for the word
        int n = hash(word_node->word);

        // Point the new node to the first element in the existing bucket
        word_node->next = table[n];

        // Make the table point to the new node
        table[n] = word_node;

        // Increase the word count in the dictionary
        word_count++;
    }

    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through hashtable
    for (int i = 0; i < N; i++)
    {
        // Set pointer to head of list
        node *cursor = table[i];

        // Traverse list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
