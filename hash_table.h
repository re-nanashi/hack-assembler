/**
 * @file hash_table.h
 * @author re-nanashi
 * @brief Hash Table public functions and datatypes
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/* size of the hash table */
#define HT_CAPACITY 50000

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
        /* a linked list that handles index collision */
        linked_list **overflow_buckets;
        int size;
        int count;
};

ht_item *create_item(char *key, char *value);

hash_table *create_table(int size);

void free_item(ht_item *item);

void free_table(hash_table *table);

void handle_collision(hash_table *table, unsigned long index, ht_item *item);

void ht_insert(hash_table *table, char *key, char *value);

char *ht_search(hash_table *table, char *key);

#endif /* HASH_TABLE_H */
