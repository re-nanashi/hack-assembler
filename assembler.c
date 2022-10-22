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
is_a_symbol(const struct token *tok)
{
        return (tok->kind == TK_RESERVED || tok->kind == TK_ID);
}

bool
is_a_command_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, "@") == 0);
}

bool
is_jmp_command_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, ";") == 0);
}

bool
is_exp_command_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, "=") == 0);
}

enum command_type
parse(struct token *tok)
{
        /* head token of the token stream */
        const struct token *const head = tok;
        bool is_c_command = false;

        // TODO
        while (!at_eoc(tok)) {
                if (is_a_command_op(head) && is_a_symbol(head->next)) {
                        is_c_command = false;
                        break;
                }

                if (head->kind == TK_RESERVED && is_jmp_command_op(head->next))
                {
                        is_c_command = true;
                }

                consume(&tok);
        }

        if (is_c_command == true)
                return C_COMMAND;
        else
                return A_COMMAND;
}

/*
 *
 * parse(hack_str_output[16 + 1], asm_command_buffer)
 * {
 *      // the token would be a list of
 *      "@" -> "i" -> eoc
 *
 *      "@" -> "i" -> eoc
 *
 *      "D" -> "=" -> "M" -> eoc
 *
 *      "D" -> "=" -> "D" -> "-" -> "A" -> eoc
 *
 *      "D" -> ";" -> "JGT" -> eoc
 *
 *      token = tokenize(asm_command_buffer);
 *
 *      case (parse_command_type(token))
 *              case C_COMMAND:
 *                      hack_str_output = generate_c_code(get_dest_mnemonic,
 * get_comp_mnemonic, get_jump_mnemonic) break;
 *
 *              case A_COMMAND:
 *                      hack_str_output = generate_a_code(asm_command_buffer)
 *                      break;
 *
 *              case L_COMMAND:
 *                      break;
 *              default:
 *                      error;
 *                      break;
 *
 *      free(token)
 *      return hack_str_output;
 * }
 *
 *
 * */

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

                while (!at_eoc(tok)) {
                        /*
                        parse(tok);
                         * 1. PARSE will return if a/c/l_command  */

                        printf("Current token kind: %s\n",
                               token_names[tok->kind]);
                        printf("Current token str: %s\n", tok->str);
                        printf("Next token address: %p\n", tok->next);

                        consume(&tok);
                        printf("New token address: %p\n", tok);
                }
                printf("EOC token kind?: %s\n", token_names[tok->kind]);

                // fprintf(out_f, "%s", asm_command_buffer);
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

        /* run assembler */
        __assemble(&hack_output_f, asm_input_f);

        fclose((FILE *)asm_input_f);
        fclose(hack_output_f);

        return 0;
}
