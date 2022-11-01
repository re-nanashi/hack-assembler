#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT 
{
    char *value;
    enum
    {
        TOKEN_RESERVED,
        TOKEN_ID,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_A_OP,
        TOKEN_EQUALS,
        TOKEN_SEMI, 
        TOKEN_OPERATOR, 
        TOKEN_INT, 
        TOKEN_EOC, 
    } type;
} token_T;

token_T *allocate_token(char *value, int type);

#endif
