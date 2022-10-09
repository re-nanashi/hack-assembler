#include <string.h>

#include "hash_table.h"

char *
gen_dest_bit(char *mnemonic)
{
        hash_table *dest_table = create_table(7);
        ht_insert(dest_table, "M", "001");
        ht_insert(dest_table, "D", "010");
        ht_insert(dest_table, "MD", "011");
        ht_insert(dest_table, "A", "100");
        ht_insert(dest_table, "AM", "101");
        ht_insert(dest_table, "AD", "110");
        ht_insert(dest_table, "AMD", "111");

        return ht_search(dest_table, mnemonic);
}

char *
gen_jump_bit(char *mnemonic)
{
        hash_table *dest_table = create_table(7);
        ht_insert(dest_table, "JGT", "001");
        ht_insert(dest_table, "JEQ", "010");
        ht_insert(dest_table, "JGE", "011");
        ht_insert(dest_table, "JLT", "100");
        ht_insert(dest_table, "JNE", "101");
        ht_insert(dest_table, "JLE", "110");
        ht_insert(dest_table, "JMP", "111");

        return ht_search(dest_table, mnemonic);
}

char *
gen_comp_bit(char *mnemonic)
{
}
