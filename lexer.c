#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/*
#include <ctype.h>
#include <stdarg.h>
*/

#include "lexer.h"

/* checks if character is a delimeter */
static bool
_is_delimiter(char ch)
{
        if (ch == ' ' || ch == '@' || ch == '=' || ch == ';' || ch == '+'
            || ch == '-' || ch == '(' || ch == ')' || ch == '&' || ch == '|'
            || ch == '\n' || ch == '\0')
                return true;

        return false;
}

/* checks if character is an operator */
static bool
_is_operator(char ch)
{
        if (ch == '@' || ch == '+' || ch == '-' || ch == '=' || ch == ';'
            || ch == '!' || ch == '&' || ch == '|' || ch == '(' || ch == ')')
                return true;

        return false;
}

/* checks if string is a valid identifier by checking if an integer is not used
 * as the starting char of the variable */
static bool
_is_valid_id(char *str)
{
        /* return false if a digit is used to begin an identifier */
        if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3'
            || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7'
            || str[0] == '8' || str[0] == '9' || _is_delimiter(str[0]) == true)
                return false;

        return true;
}

/* checks if string is a reserved keyword */
static bool
_is_keyword(char *str)
{
        if (!strcmp(str, "M") || !strcmp(str, "D") || !strcmp(str, "MD")
            || !strcmp(str, "A") || !strcmp(str, "AM") || !strcmp(str, "AD")
            || !strcmp(str, "AMD") || !strcmp(str, "JGT")
            || !strcmp(str, "JEQ") || !strcmp(str, "JGE")
            || !strcmp(str, "JLT") || !strcmp(str, "JNE")
            || !strcmp(str, "JLE") || !strcmp(str, "JMP"))
                return true;

        return false;
}

/* checks if input string is a number */
static bool
_is_integer(char *str)
{
        int i;
        /*TODO: find out exact int length: uint8_t */
        int len = strlen(str);

        if (len == 0) return false;

        for (i = 0; i < len; i++) {
                if (str[i] != '0' && str[i] != '1' && str[i] != '2'
                    && str[i] != '3' && str[i] != '4' && str[i] != '5'
                    && str[i] != '6' && str[i] != '7' && str[i] != '8'
                    && str[i] != '9')
                        return false;
        }

        return true;
}

/* extracts the substring from left index to right index from the
 * string input */
static char *
_extract_substr(char *str, int left, int right)
{
        char *substr;
        int i;

        /* verify allocation */
        substr = (char *)malloc(sizeof(char) * (right - left + 2));
        if (substr == NULL) {
                printf("Error: allocation error encountered.\n");
                exit(-1);
        }

        /* extract the substring */
        for (i = left; i <= right; i++)
                substr[i - left] = str[i];
        substr[right - left + 1] = '\0';

        return substr;
}

void
_allocate_op_token(struct token **tok, char op_char)
{
        struct token *cur_tok = *tok;

        /* convert the operator char to string */
        char str[2] = "\0";
        str[0] = op_char;

        switch (op_char) {
                case '=':
                        *tok = new_token(TOKEN_EQUALS, cur_tok, str);
                        break;
                case '@':
                        *tok = new_token(TOKEN_A_OP, cur_tok, str);
                        break;
                case '(':
                        *tok = new_token(TOKEN_LPAREN, cur_tok, str);
                        break;
                case ')':
                        *tok = new_token(TOKEN_RPAREN, cur_tok, str);
                        break;
                case ';':
                        *tok = new_token(TOKEN_SEMI, cur_tok, str);
                        break;
                default:
                        *tok = new_token(TOKEN_OP, cur_tok, str);
        }
}

struct token *
lexer_tokenize(char *cmd_buffer)
{
        /* dummy head */
        struct token head;
        head.next = NULL;
        struct token *cur_tok = &head;

        int left = 0, right = 0;
        int cb_len = strlen(cmd_buffer);
        /* loop and tokenize until the end of the command_buffer */
        while (right <= cb_len && left <= right) {
                /* if NOT delimeter */
                if (!_is_delimiter(cmd_buffer[right])) right++;

                /* if delimeter */
                if (_is_delimiter(cmd_buffer[right]) && left == right) {
                        if (_is_operator(cmd_buffer[right])) {
                                _allocate_op_token(&cur_tok,
                                                   cmd_buffer[right]);
                        }

                        right++;
                        left = right;
                }

                /* the current iterator points to a char that is not an
                 * operator or delimeter */
                if (_is_delimiter(cmd_buffer[right]) == true && left != right
                    || (right == cb_len && left != right))
                {
                        /* extracts a substring that is not an operator then
                         * determines the token kind */
                        char *substr =
                            __extract_substr(command_buffer, str_l, str_r - 1);

                        if (__is_keyword(substr) == true)
                                curr = new_token(TK_RESERVED, curr, substr);

                        else if (__is_integer(substr) == true) {
                                curr = new_token(TK_INT, curr, substr);
                                curr->val = strtol(substr, &substr, 10);
                        }

                        else if (__is_valid_id(substr) == true
                                 && __is_delimiter(command_buffer[str_r - 1])
                                        == false)
                                curr = new_token(TK_ID, curr, substr);

                        else if (__is_valid_id(substr) == false
                                 && __is_delimiter(command_buffer[str_r - 1])
                                        == false)
                        {
                                printf(
                                    "Syntax Error: Not a valid identifier.\n");
                                exit(-1);
                        }

                        else {
                                printf("Error: Cannot tokenize string.\n");
                                exit(-1);
                        }

                        str_l = str_r;
                }
        }

        /* link an EOC token at the end */
        new_token(TK_EOC, curr, "");

        return head.next;
}

struct token *
lexer_peak(struct token const *tok)
{
        if (tok->next == NULL) {
                return NULL;
        }

        return tok->next;
}

void
tk_consume(struct token **tok)
{
        if (*tok == NULL) {
                printf("Error: Cannot consume NULL token.\n");
                return;
        }

        struct token *tmp = *tok;
        *tok = tmp->next;

        /* frees the token from heap */
        tmp->next = NULL;
        free(tmp->str);
        free(tmp);
}

void
free_tk_stream(struct token **tok)
{
        while (!at_eoc(*tok)) {
                tk_consume(&(*tok));
        }
        tk_consume(&(*tok));
}
