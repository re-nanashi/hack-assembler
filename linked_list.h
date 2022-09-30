/**
 * @file linked_list.h
 * @author re-nanashi
 * @brief Simple Linked List public functions and datatypes
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* forward declaration */
typedef struct ht_item ht_item;

/* @brief The linked_list definition */
typedef struct linked_list linked_list;
struct linked_list {
    /* the hash table item */
    ht_item *item;
    linked_list *next;
};

/**
 * @brief Allocates list to memory
 *
 * @return a linked list 
 */
linked_list *allocate_list();

/**
 * @brief Insert hash table item to a list
 *
 * @param linked_list the original list
 * @param ht_item the hash table item to be inserted
 * @return the linked list with the added node
 */
linked_list *linkedlist_insert(linked_list *list, ht_item *item);

/**
 * @brief Removes the head hash table item node from the list
 *
 * This will return the removed head node
 *
 * @param linked_list the original list
 * @return the ht_item that was removed from the list 
 */
ht_item* linkedlist_remove(linked_list* list);

/**
 * @brief Frees the linked list
 *
 * @param linked_list the original list to be freed
 */
void free_linkedlist(linked_list* list);

#endif /* LINKED_LIST_H */
