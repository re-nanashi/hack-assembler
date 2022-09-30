/**
 * @file hash_table.h
 * @author re-nanashi
 * @brief Hash Table public functions and datatypes
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/* include the linked list header file */
#include "linked_list.h"

/* size of the hash table */
#define HT_CAPACITY 50000

/* @brief The hash table item definiton */
typedef struct ht_item ht_item;
struct ht_item {
        char *key;
        char *value;
};

/* @brief The hash table definiton */
typedef struct hash_table hash_table;
struct hash_table {
        /* array of pointers to items */
        ht_item **items;
        /* a linked list that handles index collision */
        linked_list **overflow_buckets;
        int size;
        int count;
};

/**
 * @brief Creates a hash table item
 *
 * @return the hash table item that was created
 */
ht_item *create_item(char *key, char *value);

/**
 * @brief Initializes a hash table 
 *
 * @param size the size of the hash table to be created
 * @return the hash table that was created
 */
hash_table *create_table(int size);

/**
 * @brief Frees the hash table item from memory
 *
 * @param item the item be freed from memory
 */
void free_item(ht_item *item);

/**
 * @brief Frees the hash table from memory
 *
 * @param table the table to be freed from memory
 */
void free_table(hash_table *table);

/**
 * @brief Inserts the key and value to a hash table
 *
 * This creates a hash table item using the key-value pair 
 *      then inserts it into the table
 *
 * @param table the table to be inserted to
 * @param key the key of the item to insert to the table
 * @param value the value of the item to be insert
 */
void ht_insert(hash_table *table, char *key, char *value);

/**
 * @brief Searches the hash table using a key
 *
 * Returns NULL if the there is no item inside the table
 *
 * @param table the table to be searched
 * @param key the key to search
 * @return the item with the given key
 */
char *ht_search(hash_table *table, char *key);

/**
 * @brief Deletes an item inside the table given a key
 *
 * @param table the table to be deleted from
 * @param key the key to delete
 */
void ht_delete(hash_table *table, char *key);

#endif /* HASH_TABLE_H */
