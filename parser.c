#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "lexer.h"

static bool
__is_acommand_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, "@") == 0);
}

static bool
__is_asymbol(const struct token *tok)
{
        return (tok->kind == TK_RESERVED || tok->kind == TK_ID
                || tok->kind == TK_INT);
}

static bool
__is_acommand(const struct token *tok)
{
        const struct token *head = tok;
        const struct token *symb = head->next;
        const struct token *eoc = symb->next;

        return (__is_acommand_op(head) && __is_asymbol(symb) && at_eoc(eoc));
}

// TODO: parse c command
static bool
__is_ccommand_valid_head(const struct token *tok)
{
        return tok->kind == TK_RESERVED
               || (tok->kind == TK_INT && tok->val == 0);
}

static bool
__is_ccommand_jmp_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, ";") == 0);
}

static bool
__is_ccommand_exp_op(const struct token *tok)
{
        return tok->kind == TK_OPERATOR && (strcmp(tok->str, "=") == 0);
}

/* NOTE: C_COMMAND is assumed when the stream starts with TK_RESERVED or
 *       TK_INT(0) followed by TK_OPERATOR(; or =) */
static bool
__is_ccommand(const struct token *tok)
{
        const struct token *const head = tok;
        const struct token *const op = head->next;

        return (__is_ccommand_valid_head(head)
                && (__is_ccommand_exp_op(op) || __is_ccommand_jmp_op(op)));
}

static bool
__is_lcommand(const struct token *tok)
{
        const struct token *lcommand_open_op = tok;
        const struct token *symb = lcommand_open_op->next;
        const struct token *lcommand_end_op = symb->next;

        bool is_lcommand_open_op =
            lcommand_open_op->kind == TK_OPERATOR
            && (strcmp(lcommand_open_op->str, "(") == 0);
        bool is_lsymbol = symb->kind == TK_ID;
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
                /* a non-command syntax error */
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

const char *
get_symb_mnemonic(const struct token *const command_tk)
{
        return command_tk->next->str;
}

const char *
get_dest_mnemonic(const struct token *const command_tk)
{
        return command_tk->str;
}

const char *
get_comp_mnemonic(const struct token *const command_tk)
{
}

const char *
get_jump_mnemonic(const char *str)
{
}
