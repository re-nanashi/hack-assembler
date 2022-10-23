/**
 * @file linked_list.h
 * @author re-nanashi
 * @brief Simple Linked List public functions and datatypes
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//TODO
/* forward declaration */
struct ht_item;

/* @brief The linked_list definition */
struct linked_list {
    /* the hash table item */
    struct ht_item *item;
    struct linked_list *next;
};

/**
 * @brief Allocates list to memory
 *
 * @return a linked list 
 */
struct linked_list *allocate_list();

/**
 * @brief Insert hash table item to a list
 *
 * @param linked_list the original list
 * @param ht_item the hash table item to be inserted
 * @return the linked list with the added node
 */
struct linked_list *linkedlist_insert(struct linked_list *list, struct ht_item *item);

/**
 * @brief Removes the head hash table item node from the list
 *
 * This will return the removed head node
 *
 * @param linked_list the original list
 * @return the ht_item that was removed from the list 
 */
struct ht_item* linkedlist_remove(struct linked_list* list);

/**
 * @brief Frees the linked list
 *
 * @param linked_list the original list to be freed
 */
void free_linkedlist(struct linked_list* list);

#endif /* LINKED_LIST_H */
