#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "hash_table.h"
#include "parser.h"
#include "lexer.h"

#define C_BUFFER_SIZE    1000
#define BITC_BUFFER_SIZE 16

const char *token_names[] = { "TK_RESERVED", "TK_ID", "TK_OPERATOR", "TK_INT",
                              "TK_EOC" };

/*
void
__new_error_wrapper(char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, "\n");
        exit(1);
}
*/

static void
__assemble(FILE **output_f, const FILE *const input_f)
{
        const FILE *in_f = input_f;
        FILE *out_f = *output_f;
        /* check memory allocation */
        if (in_f == NULL) {
                printf("Error: Could not open file.\n");
                exit(-1);
        }

        /* create and allocate a token */
        struct token *tok = allocate_token();
        char asm_command_buffer[C_BUFFER_SIZE + 1];

        /* loop while file stream has more code to parse */
        while (fgets(asm_command_buffer, C_BUFFER_SIZE + 1, (FILE *)in_f)
               != NULL) {
                /* asm_command_buffer is the current code until eoc */
                /* TODO: We have to parse the buffer */
                /* strcpy(string_output, parse(in)) */
                tok = tokenize(asm_command_buffer);

                switch (parse(tok)) {
                case A_COMMAND:
                        break;
                case C_COMMAND:
                        break;
                case L_COMMAND:
                default:
                        break;
                }

                fprintf(out_f, "%s\n", print_command_type(parse(tok)));

                free_tk_stream(&tok);
        }
}

int
main(int argc, char **argv)
{
        /** TODO: Create an error wrapper.
         *        1. approriate file extension
         *        2. COMMENT
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
        /* check memory allocation */
        if (hack_output_f == NULL || asm_input_f == NULL) {
                exit(-1);
        }

        /* run assembler */
        __assemble(&hack_output_f, asm_input_f);

        fclose((FILE *)asm_input_f);
        fclose(hack_output_f);

        return 0;
}
