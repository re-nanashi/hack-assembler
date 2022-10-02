#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

void
print_search(hash_table *table, char *key)
{
        char *val;
        if ((val = ht_search(table, key)) == NULL) {
                printf("%s does not exist\n", key);
                return;
        }
        else {
                printf("Key:%s, Value:%s\n", key, val);
        }
}

void
print_table(hash_table *table)
{
        printf("\n-------------------\n");
        for (int i = 0; i < table->size; i++) {
                if (table->items[i]) {
                        printf("Index:%d, Key:%s, Value:%s", i,
                               table->items[i]->key, table->items[i]->value);
                        if (table->overflow_buckets[i]) {
                                printf(" => Overflow Bucket => ");
                                linked_list *head = table->overflow_buckets[i];
                                while (head) {
                                        printf("Key:%s, Value:%s ",
                                               head->item->key,
                                               head->item->value);
                                        head = head->next;
                                }
                        }
                        printf("\n");
                }
        }
        printf("-------------------\n");
}

void
hash_table_sample_code(void)
{
        {
                hash_table *ht = create_table(HT_CAPACITY);
                ht_insert(ht, "1", "First address");
                ht_insert(ht, "2", "Second address");
                ht_insert(ht, "Hel", "Third address");
                ht_insert(ht, "Cau", "Fourth address");
                print_search(ht, "1");
                print_search(ht, "2");
                print_search(ht, "3");
                print_search(ht, "Hel");
                print_search(ht, "Cau"); // Collision!
                print_table(ht);
                ht_delete(ht, "1");
                ht_delete(ht, "Cau");
                print_table(ht);
                free_table(ht);
        }
}

void
__assemble(FILE **output_f, FILE **input_f)
{
}

int
main(int argc, char **argv)
{
        /** TODO: Create an error wrapper.
         *        1. approriate file extension
         */
        if (argc != 2) {
                printf("Error: Number of parameters.");
                return 1;
        }

        /**
         * TODO: the output file should have the same name as the input
         *       or have the option to enter the file name of the output
         *       with the -o flag
         */
        FILE *asm_input_f = fopen(argv[1], "r");
        FILE *hack_output_f = fopen("output.hack", "w");

        __assemble(&asm_input_f, &hack_output_f);

        fclose(asm_input_f);
        fclose(hack_output_f);

        return 0;
}
