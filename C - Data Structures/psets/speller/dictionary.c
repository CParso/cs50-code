// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Variable to be used to count each word to be returned in size
int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Retrieve hash key
    int hash_key = hash(word);

    // Cursor pointing to start of bucket indicated by hash key
    node *cursor = table[hash_key];

    // Loop through linked list searching for the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            // If it exists in linked list return true
            return true;
        }
        // Move the cursor along
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Convert first two letters to lower case
    char letter1 = tolower(word[0]);
    char letter2 = tolower(word[1]);

    // Retrieve their ASCII values and normalise them
    int sum = ((letter1 - 'A') + (letter2 - 'A')) % N;

    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Declare a buffer for fscanf function
    char word[LENGTH + 1];

    // Scan the file for strings until it reaches the end of the file
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the word from dictionary to node
        strcpy(n->word, word);

        // Retrieve hash key
        int hash_key = hash(word);

        // Initialise pointer to next node
        n->next = table[hash_key];

        // Assign node pointer to the position returned by hash function
        table[hash_key] = n;

        // Increase word count
        num_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // For each bucket
    for (int i = 0; i < N; i++)
    {
        // Point cursor to start of list
        node *cursor = table[i];

        // Loop through list freeing memory until it reaches the end
        while (cursor != NULL)
        {
            node *tmp = cursor;

            cursor = cursor->next;

            free(tmp);
        }

        // If the for loop is at its end and the cursor has reached the end of its final list
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
