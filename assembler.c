#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hash_table.h"

#define C_BUFFER_SIZE 1000

enum command_type { A_COMMAND, C_COMMAND, L_COMMAND };

/*NOTE: Do not include L_COMMAND for now */
enum command_type
parse_command_type()
{
}

static void
__assemble(FILE **output_f, const FILE *const input_f)
{
        if (output_f == NULL || input_f == NULL) {
                exit(-1);
        }

        const FILE *in_f = input_f;
        FILE *out_f = *output_f;
        if (in_f == NULL) {
                printf("Error: Could not open file.\n");
                exit(-1);
        }

        char asm_command_buffer[C_BUFFER_SIZE + 1];
        /* loop while file stream has more code to parse */
        while (fgets(asm_command_buffer, C_BUFFER_SIZE + 1, (FILE *)in_f)
               != NULL) {
                /* asm_command_buffer is the current code */
                /* TODO: We have to parse the buffer */
                fprintf(out_f, "%s", asm_command_buffer);
        }
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
        const FILE *const asm_input_f = fopen(argv[1], "r");
        FILE *hack_output_f = fopen("output.hack", "w");

        /* run assembler */
        __assemble(&hack_output_f, asm_input_f);

        fclose((FILE *)asm_input_f);
        fclose(hack_output_f);

        return 0;
}
