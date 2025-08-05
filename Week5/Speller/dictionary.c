// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hashing the word
    unsigned int index = hash(word);

    // Traverse the linked lists at that bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    // If word not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    // Loop through the word
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Updating unique value for each letter in the word in hash
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;
}

// Initializing a variable for word_count
static int word_count = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *source = fopen (dictionary, "r");

    // Check if file opened correctly
    if (source == NULL)
    {
        return false;
    }

    // Initialize the Hash table pointers
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read the strings from the file until the EOF
    char word[LENGTH + 1];
    while (fscanf (source, "%s", word) != EOF)
    {
        // Create a new node
        node *newnode = malloc (sizeof (node));
        if(newnode == NULL)
        {
            fclose(source);
            return false;
        }

        // Copy the word into the node
        strcpy (newnode->word, word);
        newnode->next = NULL;

        // Getting the hash number from hash function
        unsigned int index = hash(word);

        // Placing the node in the hash table
        newnode->next = table[index];
        table[index] = newnode;

        // Increase the word_coun
        word_count++;
    }
    fclose(source);
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
    // Loop to get to all the buckets
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        // Traversing through each linked list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
