// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


const unsigned int N = 100;// Number of buckets in hash table
unsigned int dictionarySize = 0;//size of dictionary
bool isDictionaryLoaded = false;//tell if dictionary is already loaded

// Hash table
node *table[N];


// Hashes word to a number
//this function uses sdbm hash Code
//http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{

    unsigned int h = 0;
    int c;

    while ((c = tolower(*word++)))
    {
    h = c + (h << 6) + (h << 16) - h;

    }

    h = h % N;
    return h;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{

    unsigned int hashWord = hash(word);
    node *cursor = table[hashWord];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
            return true;

        cursor = cursor->next;
    }

    return false;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //try to open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    //read each word from dictionary
    char word[LENGTH + 1];
    node *tempNode;
    unsigned int hashIndex;
    while (fscanf(file, "%s", word) != EOF)
    {
        tempNode = malloc(sizeof(node));
        if (tempNode == NULL)
        {
            return false;
        }
        strcpy(tempNode->word, word);
        tempNode->next = NULL;

        hashIndex = hash(word);

        //check if alread have value at that position
        if (table[hashIndex] != NULL)
        {
            tempNode->next = table[hashIndex];
            table[hashIndex] = tempNode;
        }
        else
        {
            table[hashIndex] = tempNode;
        }
        dictionarySize++;
    }

    if (ferror(file))
    {
        fclose(file);
        unload();
        return false;
    }
    fclose(file);
    isDictionaryLoaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (isDictionaryLoaded)
        return dictionarySize;
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;
    for (unsigned int i = 0; i < N; i++)
    {
        cursor = table[i];
        table[i] = NULL;
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            tmp = NULL;
        }
        //check if table still have any value
        if (table[i])
        {
            return false;
        }
    }
    return true;
}
