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

bool
__is_acommand_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, "@") == 0);
}

bool
__is_asymbol(const struct token *tok)
{
        return (tok->kind == TK_RESERVED || tok->kind == TK_ID
                || tok->kind == TK_INT);
}

bool
__is_acommand(const struct token *tok)
{
        const struct token *head = tok;
        const struct token *symb = head->next;
        const struct token *eoc = symb->next;

        return (__is_acommand_op(head) && __is_asymbol(symb) && at_eoc(eoc));
}

bool
__is_ccommand_valid_head(const struct token *tok)
{
        return tok->kind == TK_RESERVED
               || (tok->kind == TK_INT && tok->val == 0);
}

bool
__is_ccommand_jmp_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, ";") == 0);
}

bool
__is_ccommand_exp_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, "=") == 0);
}

/* NOTE: C_COMMAND is assumed when the stream starts with TK_RESERVED or
 *       TK_INT(0) followed by TK_OPERATOR(; or =) */
bool
__is_ccommand(const struct token *tok)
{
        const struct token *const head = tok;
        const struct token *const op = head->next;

        return (__is_ccommand_valid_head(head)
                && (__is_ccommand_exp_op(op) || __is_ccommand_jmp_op(op)));
}

bool
__is_lcommand(const struct token *tok)
{
        const struct token *lcommand_open_op = tok;
        const struct token *symbol = lcommand_open_op->next;
        const struct token *lcommand_end_op = symbol->next;

        bool is_lcommand_open_op =
            lcommand_open_op->kind == TK_OPERATOR
            && (strcmp(lcommand_open_op->str, "(") == 0);
        bool is_lsymbol = symbol->kind == TK_ID;
        bool is_lcommand_end_op = lcommand_end_op->kind == TK_OPERATOR
                                  && (strcmp(lcommand_end_op->str, ")") == 0);

        return is_lcommand_open_op && is_lsymbol && is_lcommand_end_op;
}

enum command_type
parse(struct token *tk_stream)
{
        enum command_type ret;

        if (__is_acommand(tk_stream)) {
                ret = A_COMMAND;
        }

        else if (__is_ccommand(tk_stream)) {
                ret = C_COMMAND;
        }

        else if (__is_lcommand(tk_stream)) {
                ret = L_COMMAND;
        }

        else {
                /* a non-command error */
                printf("Syntax Error: No such command.\n");
                exit(-1);
        }

        return ret;
}

const char *
print_command_type(int ct)
{
        const char *command_types[] = { "A_COMMAND", "C_COMMAND",
                                        "L_COMMAND" };

        return command_types[ct];
}

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

        /* create a token here */
        struct token *tok = allocate_token();
        char asm_command_buffer[C_BUFFER_SIZE + 1];

        /* loop while file stream has more code to parse */
        while (fgets(asm_command_buffer, C_BUFFER_SIZE + 1, (FILE *)in_f)
               != NULL) {
                /* asm_command_buffer is the current code until eoc */
                /* TODO: We have to parse the buffer */
                /* strcpy(string_output, parse(in)) */
                tok = tokenize(asm_command_buffer);

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
