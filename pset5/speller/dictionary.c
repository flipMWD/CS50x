// Implements a dictionary's functionality

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
int base = 26, expo = 3;
const unsigned int N = 17576; //676; // N = pow(base, expo)

// Hash table
node *table[N];

unsigned int word_count = 0;

bool search_word(const char *word, node *head)
{
    char lcw[LENGTH + 1];
    int i;
    for (i = 0; word[i]; ++i)
    {
        lcw[i] = (char) tolower(word[i]);
    }
    lcw[i] = '\0';

    node *temp = head;
    while (temp)
    {
        if (strcmp(lcw, temp->word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    if (search_word(word, table[hash(word)]))
    {
        return true;
    }

    return false;
}

node *insert_word(const char *word, node *head)
{
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL)
    {
        return NULL;
    }

    strcpy(new_node->word, word);
    new_node->next = NULL;
    if (head != NULL)
    {
        new_node->next = head;
    }
    head = new_node;

    return head;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    for (int i = 0, j = 0; i < expo; ++i, ++j)
    {
        int c;
        bool bw = false;
        // Move forward till find a non ' or \0, move backward till find an alpha
        while (j > 0 && ((c = tolower(word[j])) == '\'' || (bw = (c == 0) ? true : false)))
        {
            j += (!bw) ? 1 : -1;
        }

        c = tolower(word[j]) - 'a';
        index += (unsigned int) c * pow(base, (expo - 1) - i);
    }

    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict_buffer = fopen(dictionary, "r");
    if (dict_buffer == NULL)
    {
        fclose(dict_buffer);
        return false;
    }

    int ret;
    char word[LENGTH + 1];
    while ((ret = fscanf(dict_buffer, "%s", word)) != EOF)
    {
        if (!(table[hash(word)] = insert_word(word, table[hash(word)])))
        {
            return false;
        }
        word_count++;
    }

    fclose(dict_buffer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

bool remove_words(node *head)
{
    node *temp = head;
    while (temp)
    {
        head = temp->next;
        free(temp);
        temp = head;
    }

    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    bool wu;
    for (int i = 0; i < N; ++i)
    {
        if (!(wu = remove_words(table[i])))
        {
            printf("Unload failed.\n");
            return false;
        }
    }

    return true;
}

// vim:sw=4:et
