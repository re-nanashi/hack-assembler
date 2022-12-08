#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "token.h"

struct token *
allocate_token(void)
{
        struct token *tok;

        /* verify allocation */
        tok = (struct token *)calloc(1, sizeof(struct token));
        if (tok == NULL) {
                printf("Error: allocation error encountered.\n");
                exit(-1);
        }

        return tok;
}

struct token *
new_token(token_type_t tok_type, struct token *cur_tok, char *str)
{
        /* allocate token to memory */
        struct token *tok;
        tok = allocate_token();

        tok->str = (char *)malloc(strlen(str) + 1);
        tok->type = tok_type;
        strcpy(tok->str, str);
        cur_tok->next = tok;

        return tok;
}

bool
token_is_eoc(struct token const *cur_tok)
{
        return TOKEN_EOC == cur_tok->type;
}
