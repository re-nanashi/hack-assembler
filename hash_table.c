#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash_table.h"
#include "linked_list.h"

unsigned long
_hash_function(char *str)
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

static linked_list **
_create_overflow_buckets(hash_table *table)
{
        /* create the overflow buckets; an array of linkedlists */
        linked_list **buckets =
            (linked_list **)calloc(table->size, sizeof(linked_list **));

        for (int i = 0; i < table->size; i++)
                buckets[i] = NULL;

        return buckets;
}

hash_table *
create_table(int size)
{
        /* creates a new hash_table */
        hash_table *table = (hash_table *)malloc(sizeof(hash_table));

        table->size = size;
        table->count = 0;
        table->overflow_buckets = _create_overflow_buckets(table);
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

static void
_free_overflow_buckets(hash_table *table)
{
        /* free all the overflow buckets */
        linked_list **buckets = table->overflow_buckets;

        for (int i = 0; i < table->size; i++)
                free_linkedlist(buckets[i]);

        free(buckets);
}

void
free_table(hash_table *table)
{
        /* frees the items within the hash_table */
        for (int i = 0; i < table->size; i++) {
                ht_item *item = table->items[i];
                if (item != NULL) free_item(item);
        }

        /* frees the overflow bucket and it's items */
        _free_overflow_buckets(table);

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
        int index = _hash_function(key);

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
                        handle_collision(table, index, item);
                        return;
                }
        }
}

void
handle_collision(hash_table *table, unsigned long index, ht_item *item)
{
        linked_list *head = table->overflow_buckets[index];

        if (head == NULL) {
                /* create the overflow list */
                head = allocate_list();
                head->item = item;
                table->overflow_buckets[index] = head;

                return;
        }
        else {
                /* insert to the list */
                table->overflow_buckets[index] = linkedlist_insert(head, item);

                return;
        }
}

char *
ht_search(hash_table *table, char *key)
{
        /* search the key in the hash table */
        int index = _hash_function(key);
        ht_item *item = table->items[index];
        linked_list *head = table->overflow_buckets[index];

        /* ensure that we move to items inside the overflow list that are not
         * NULL */
        while (item != NULL) {
                if (strcmp(item->key, key) == 0) return item->value;
                /* no collision chain exists */
                if (head == NULL) return NULL;

                item = head->item;
                head = head->next;
        }

        return NULL;
}

void
_handle_collision_delete_node(linked_list **llist, int index, char *key)
{
        linked_list *current = *llist, *previous = NULL;

        while (current != NULL) {
                if (strcmp(current->item->key, key) == 0) {
                        /* the first node(head) of the collision chain*/
                        if (previous == NULL) {
                                /* adjust the the current head to head->next */
                                *llist = current->next;

                                /* free the old node */
                                current->next = NULL;
                                free_linkedlist(current);

                                return;
                        }
                        /* the node to delete is in the list */
                        else {
                                /* unlink the node from the linked list*/
                                linked_list *node = current;
                                previous->next = current->next;

                                /* free the current node */
                                node->next = NULL;
                                free_linkedlist(node);

                                return;
                        }
                }

                previous = current;
                current = current->next;
        }
}

void
ht_delete(hash_table *table, char *key)
{
        /* deletes an item from the table */
        int index = _hash_function(key);
        ht_item *item = table->items[index];
        linked_list *overflow_llist_head = table->overflow_buckets[index];

        if (item == NULL) /* item does not exist */
                return;
        else {
                /* the current item is to be deleted and no collision chain
                 * exists */
                if (overflow_llist_head == NULL && strcmp(item->key, key) == 0)
                {
                        /* no collision chain; remove the item */
                        table->items[index] = NULL;
                        free_item(item);
                        table->count--;

                        return;
                }
                /* collision chain exist */
                else if (overflow_llist_head != NULL) {
                        /* the item to be removed is the head */
                        if (strcmp(item->key, key) == 0) {
                                /* remove the item; set the head as the new
                                 * item */
                                free_item(item);

                                /* create a temp node for the item */
                                linked_list *node = overflow_llist_head;

                                /* adjust the new head of the chain */
                                overflow_llist_head =
                                    overflow_llist_head->next;
                                table->overflow_buckets[index] =
                                    overflow_llist_head;

                                /* create a new item using node as the ref */
                                node->next = NULL;
                                table->items[index] = create_item(
                                    node->item->key, node->item->value);

                                free_linkedlist(node);

                                return;
                        }

                        /* handle node deletion; delete inside the list */
                        _handle_collision_delete_node(
                            &table->overflow_buckets[index], key);
                }
        }
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
