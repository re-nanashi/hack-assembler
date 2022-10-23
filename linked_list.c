#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "hash_table.h"

struct linked_list *
allocate_list()
{
        /* allocates memory for a linked list pointer */
        struct linked_list *list =
            (struct linked_list *)malloc(sizeof(struct linked_list));
        return list;
}

struct linked_list *
linkedlist_insert(struct linked_list *list, struct ht_item *item)
{
        /* inserts the item into the linked list */
        if (!list) {
                struct linked_list *head = allocate_list();
                head->item = item;
                head->next = NULL;
                list = head;
                return list;
        }

        else if (list->next == NULL) {
                struct linked_list *node = allocate_list();
                node->item = item;
                node->next = NULL;
                list->next = node;
                return list;
        }

        /* iterate the list until the tail of the list */
        struct linked_list *tmp = list;
        while (tmp->next->next) {
                tmp = tmp->next;
        }

        struct linked_list *node = allocate_list();
        node->item = item;
        node->next = NULL;
        tmp->next = node;

        return list;
}

struct ht_item *
linkedlist_remove(struct linked_list *list)
{
        /* removes the head from the linked_list */
        /* and returns the removed item */
        if (!list) return NULL;
        if (!list->next) return NULL;

        struct linked_list *node = list->next;
        struct linked_list *tmp = list;
        tmp->next = NULL;
        list = node;

        /* copy the contents of the head of the list to item */
        struct ht_item *item = NULL;
        memcpy(item, tmp->item, sizeof(struct ht_item));

        /* free memory */
        free(tmp->item->key);
        free(tmp->item->value);
        free(tmp->item);
        free(tmp);

        return item;
}

void
free_linkedlist(struct linked_list *list)
{
        struct linked_list *tmp;
        while (list != NULL) {
                tmp = list;
                list = list->next;
                free(tmp->item->key);
                free(tmp->item->value);
                free(tmp->item);
                free(tmp);
        }
}
