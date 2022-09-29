#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

linked_list *
allocate_list()
{
        /* allocates memory for a linked list pointer */
        linked_list *list = (linked_list *)malloc(sizeof(linked_list));
        return list;
}

linked_list *
linkedlist_insert(linked_list *list, ht_item *item)
{
        /* inserts the item into the linked list */
        if (!list) {
                linked_list *head = allocate_list();
                head->item = item;
                head->next = NULL;
                list = head;
                return list;
        }
        else if (list->next == NULL) {
                linked_list *node = allocate_list();
                node->item = item;
                node->next = NULL;
                list->next = node;
                return list;
        }

        /* iterate the list until the tail of the list */
        linked_list *tmp = list;
        while (tmp->next->next) {
                tmp = tmp->next;
        }

        linked_list *node = allocate_list();
        node->item = item;
        node->next = NULL;
        tmp->next = node;

        return list;
}

ht_item *
linkedlist_remove(linked_list *list)
{
        /* removes the head from the linked_list */
        /* and returns the removed item */
        if (!list) return NULL;
        if (!list->next) return NULL;

        linked_list *node = list->next;
        linked_list *tmp = list;
        tmp->next = NULL;
        list = node;

        /* copy the contents of the head of the list to item */
        ht_item *item = NULL;
        memcpy(item, tmp->item, sizeof(ht_item));

        /* free memory */
        free(tmp->item->key);
        free(tmp->item->value);
        free(tmp->item);
        free(tmp);

        return item;
}

void
free_linkedlist(linked_list *list)
{
        linked_list *tmp;
        while (list != NULL) {
                tmp = list;
                list = list->next;
                free(tmp->item->key);
                free(tmp->item->value);
                free(tmp->item);
                free(tmp);
        }
}
