// Implements a dictionary's functionality

#include <cs50.h>
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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 2111;

// counts number of words in dictionary while being loaded
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hashes word being checked
    unsigned int h = hash(word);
    node *cursor = table[h];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else if (strcasecmp(cursor->word, word) != 0 && cursor->next != NULL)
        {
            cursor = cursor->next;
        }
        else
        {
            return false;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // hash function: uppercase every character in word, then finds %(mod) 2287 of the number and returns value
    /*
    sources used:
    https://www.geeksforgeeks.org/hash-functions-and-list-types-of-hash-functions/
    https://en.wikipedia.org/wiki/List_of_prime_numbers
    */
    unsigned int m = 1;
    for (int i = 0, j = strlen(word); i < j; i++)
    {
        m *= toupper(word[i]);
    }
    return m = m % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // opens dictionary to be read; creates input pointer
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("File could not be opened.\n");
        return false;
    }

    // creates string (char *) to store current word being read from dictionary
    char *dictword = malloc(sizeof(char) * (LENGTH + 1));

    // writes word from dictionary into newnode
    while (fscanf(inptr, "%s", dictword) != EOF)
    {
        // creates new node, copies dictword into new node, sets pointer in current node (n->next) to next node to NULL
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Memory Error\n");
            return false;
        }
        // copies word from dictionary and adds it to appropriate hash table
        unsigned int hashval = hash(dictword);
        strcpy(n->word, dictword);
        n->next = table[hashval];
        table[hashval] = n;
        count++;
    }
    free(dictword);
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size()
{
    // TODO
    // uses global count variable
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *tmp;
        node *cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
    return true;
}
