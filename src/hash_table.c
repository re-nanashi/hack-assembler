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
        /* array of pointers to items */
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

ht_item *
create_item(char *key, char *value)
{
        /* creates a pointer to a new hash table item */
        ht_item *item = (ht_item *)malloc(sizeof(ht_item));
        item->key = (char *)malloc(strlen(key) + 1);
        item->value = (char *)malloc(strlen(value) + 1);

        strcpy(item->key, key);
        strcpy(item->value, value);

        return item;
}

hash_table *
create_table(int size)
{
        /* creates a new hash_table */
        hash_table *table = (hash_table *)malloc(sizeof(hash_table));
        table->size = size;
        table->count = 0;
        table->items = (ht_item **)calloc(table->size, sizeof(ht_item *));

        for (int i = 0; i < table->size; i++)
                table->items[i] = NULL;

        return table;
}

void
free_item(ht_item *item)
{
        /* free a hash_table item */
        free(item->key);
        free(item->value);
        free(item);
}

void
free_table(hash_table *table)
{
        /* frees the items within the hash_table */
        for (int i = 0; i < table->size; i++) {
                ht_item *item = table->items[i];
                if (item != NULL) free_item(item);
        }

        /* free the table */
        free(table->items);
        free(table);
}
