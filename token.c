#include "token.h"

struct token_T *
allocate_token(enum TokenType type, char *value)
{
        struct token_T *token = calloc(1, sizeof(struct token_T));
        token->svalue = value;
        token->type = type;

        return token;
}

struct token_T *
new_token(struct token_T **token, enum TokenType type, char *value)
{
        struct token_T *node = allocate_token(type, value);
        struct token_T *head = *token;
        head->next = node;

        head = head->next;
}
