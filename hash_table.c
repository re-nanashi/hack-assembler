#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash_table.h"
#include "linked_list.h"

unsigned long
hash_function(char *str)
{
        unsigned long i = 0;

        for (int j = 0; str[j]; j++)
                i += str[j];

        return i % HT_CAPACITY;
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

void
ht_insert(hash_table *table, char *key, char *value)
{
        /* create the hash table item*/
        ht_item *item = create_item(key, value);

        /* compute the index */
        int index = hash_function(key);

        ht_item *current_item = table->items[index];
        /* if the key does not exist */
        if (current_item == NULL) {
                /* if the table is already full */
                if (table->count == table->size) {
                        printf("Error: Hash Table is full.\n");
                        free_item(item);
                        return;
                }

                /* insert directly */
                table->items[index] = item;
                table->count++;
        }
        else {
                /* if we have to update only the value */
                if (strcmp(current_item->key, key) == 0) {
                        free(current_item->value);
                        current_item->value =
                            (char *)malloc(strlen(value) + 1);
                        strcpy(current_item->value, value);
                        return;
                }
                else {
                        /* TODO handle_collision function */
                        handle_collision(table, item);
                        return;
                }
        }
}

// TODO
void
handle_collision(hash_table *table, ht_item *item)
{
}

char *
ht_search(hash_table *table, char *key)
{
        /* search the key in the hash table */
        int index = hash_function(key);
        // TODO: search the linked list
        ht_item *item = table->items[index];

        /* returns NULL if it doesn't exist */
        if (item != NULL) {
                if (strcmp(item->key, key) == 0) {
                        return item->value;
                }
        }

        return NULL;
}

void
print_search(hash_table *table, char *key)
{
        char *val;
        if ((val = ht_search(table, key)) == NULL) {
                printf("Key:%s does not exist\n", key);
                return;
        }
        else {
                printf("Key:%s, Value:%s\n", key, val);
        }
}

void
print_table(hash_table *table)
{
        printf("\nHash Table\n-----------\n'");
        for (int i = 0; i < table->size; i++) {
                // Not Null
                if (table->items[i]) {
                        printf("Index:%d, Key:%s, Value:%s\n", i,
                               table->items[i]->key, table->items[i]->value);
                }
        }
        printf("------------------\n\n");
}

int
main()
{
        hash_table *ht = create_table(HT_CAPACITY);
        ht_insert(ht, "1", "First address");
        ht_insert(ht, "2", "Second address");
        print_search(ht, "1");
        print_search(ht, "2");
        print_search(ht, "3");
        print_table(ht);
        free_table(ht);

        return 0;
}
