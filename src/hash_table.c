#include <stdlib.h>
#include <string.h>

/* size of the hash table */
#define CAPACITY 50000

typedef struct ht_item ht_item;

/* hash table item definiton */
struct ht_item {
        char *key;
        char *value;
};

typedef struct hash_table hash_table;

/* hash table definiton */
struct hash_table {
        /* array of pointers  to items */
        ht_item **items;
        int size;
        int count;
};

unsigned long
hash_function(char *str)
{
        unsigned long i = 0;

        for (int j = 0; str[j]; j++)
                i += str[j];

        return i % CAPACITY;
}
