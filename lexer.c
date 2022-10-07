#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

/** TODO:
 *  Create a:
 *      1. tokenizer
 *      2. consume function
 *      3. peek function
 **/

typedef enum {
        TK_RESERVED,
        TK_ID,
        TK_OPERATOR,
        TK_INT,
        TK_EOC,
        TK_EOF,
} token_kind;

/* @brief Token struct */
struct token {
        token_kind kind;
        struct token *next;
        char *str;
        int val;
};

bool
__is_delimiter(char ch)
{
        if (ch == ' ' || ch == '@' || ch == '=' || ch == ';' || ch == '+'
            || ch == '-' || ch == '(' || ch == ')' || ch == '&' || ch == '|')
                return true;

        return false;
}

bool
__is_operator(char ch)
{
        if (ch == '@' || ch == '+' || ch == '-' || ch == '=' || ch == ';'
            || ch == '!' || ch == '&' || ch == '|')
                return true;

        return false;
}

bool
__is_valid_id(char *str)
{
        if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3'
            || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7'
            || str[0] == '8' || str[0] == '9'
            || __is_delimiter(str[0]) == true)
                return false;

        return true;
}

bool
__is_keyword(char *str)
{
        if (!strcmp(str, "@") || !strcmp(str, "M") || !strcmp(str, "D")
            || !strcmp(str, "MD") || !strcmp(str, "A") || !strcmp(str, "AM")
            || !strcmp(str, "AD") || !strcmp(str, "AMD") || !strcmp(str, "JGT")
            || !strcmp(str, "JEQ") || !strcmp(str, "JGE")
            || !strcmp(str, "JLT") || !strcmp(str, "JNE")
            || !strcmp(str, "JLE") || !strcmp(str, "JMP"))
                return true;

        return false;
}

bool
__is_integer(char *str)
{
        int i;
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

char *
__extract_substr(char *str, int left, int right)
{
        int i;
        char *substr = (char *)malloc(sizeof(char) * (right - left + 2));

        for (i = left; i <= right; i++)
                substr[i - left] = str[i];
        substr[right - left + 1] = '\0';

        return substr;
}

bool
__at_eoc(struct token const *cur)
{
        return TK_EOC == cur->kind;
}

bool
__at_eof(struct token const *cur)
{
        return TK_EOF == cur->kind;
}

struct token *
allocate_token(void)
{
        struct token *tok = (struct token *)malloc(sizeof(struct token));
        return tok;
}

struct token *
new_token(token_kind tk_kind, struct token *cur, char *str)
{
        struct token *tok = calloc(1, sizeof(struct token));
        tok->str = (char *)malloc(strlen(str) + 1);

        tok->kind = tk_kind;
        strcpy(tok->str, str);
        cur->next = tok;

        return tok;
}

struct token *
tokenize(char *command_buffer)
{
        struct token *head = (struct token *)malloc(sizeof(struct token));
        head->next = NULL;
        struct token *curr = head;

        int str_l = 0, str_r = 0;
        int cb_len = strlen(command_buffer);
        while (str_r <= cb_len && str_l <= str_r) {
                if (__is_delimiter(command_buffer[str_r]) == false) str_r++;

                if (__is_delimiter(command_buffer[str_r]) == true
                    && str_l == str_r) {
                        if (__is_operator(command_buffer[str_r]) == true)
                                curr = new_token(TK_OPERATOR, curr,
                                                 &command_buffer[str_r]);
                        str_r++;
                        str_l = str_r;
                }

                if (__is_delimiter(command_buffer[str_r]) == true
                        && str_l != str_r
                    || (str_r == cb_len && str_l != str_r))
                {

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
                                printf("Error: Not a valid identifier");
                                exit(-1);
                        }

                        // TODO: condition for other tokens
                }
        }
}
