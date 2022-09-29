/**
 * @file linked_list.h
 * @author re-nanashi
 * @brief Simple Linked List public functions and datatypes
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_list linked_list;

/* linked_list definition */
struct linked_list {
    ht_item *item;
    linked_list *next;
    
};

linked_list *linkedlist_insert(linked_list *list, ht_item *item);

ht_item* linkedlist_remove(linked_list* list);

void free_linkedlist(linked_list* list);

#endif /* HASH_TABLE_H */
