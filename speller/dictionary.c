// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int letterAmount = 3;
const unsigned int alphabetLength = 26;
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char wordLower[LENGTH + 1];
    for (int i = 0; true; i++)
    {
        wordLower[i] = tolower(word[i]);
        if (word[i] == '\0')
        {
            break;
        }
    }

    unsigned int hashNumber = hash(word);
    node *p = table[hashNumber];
    while (p != NULL)
    {
        if (strcmp(p->word, wordLower) == 0)
        {
            return true;
        }
        else
        {
            p = p->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashNumber = 0;

    for (int i = 0, loops = 0; loops < letterAmount; i++, loops++)
    {
        if (word[i] == '\0')
        {
            break;
        }
        else if ((word[i] <= 'z' && word[i] >= 'a') || (word[i] <= 'Z' && word[i] >= 'A'))
        {
            hashNumber += (toupper(word[i]) - 'A') * pow(26, (letterAmount - 1 - i));
        }
        else
        {
            loops--;
        }
    }
    return hashNumber;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char inputWord[LENGTH + 2];
    int words = 0;
    while (fgets(inputWord, LENGTH + 2, dict))
    {
        int i = 0;
        while (inputWord[i] != '\n')
        {
            i++;
        }
        inputWord[i] = '\0';

        int hashNumber = hash(inputWord);
        node *newWord = malloc(sizeof(node));
        strcpy(newWord->word, inputWord);
        newWord->next = table[hashNumber];
        table[hashNumber] = newWord;
        words++;
    }

    fclose(dict);

    if (words == size())
    {
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *p = table[i];
            while (p != NULL)
            {
                p = p->next;
                counter++;
            }
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int words = 0;
    int dictSize = size();
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *p = table[i];
            while (p != NULL)
            {
                p = p->next;
                free(table[i]);
                words++;
                table[i] = p;
            }
        }
    }
    if (words == dictSize)
    {
        return true;
    }
    return false;
}
