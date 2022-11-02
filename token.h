/**
 * @file token.h
 * @author re-nanashi
 * @brief Token public functions and data types
 */

#ifndef TOKEN_H
#define TOKEN_H

/* @brief Types of token */
enum TokenType {
        /* single-character tokens */
        TK_LPAREN = 0,
        TK_RPAREN,
        TK_OPERATOR, 
        TK_A_OP,
        TK_EQUALS,
        TK_SEMI, 
        /* literals */
        TK_INT, 
        TK_ID,
        /* keywords */
        TK_RESERVED, 
        TK_RESERVED_JMP, 
        TK_RESERVED_DEST, 
        /* end-of-command */
        TK_EOC, 
};

/* @brief Token struct */
struct token_T 
{
    /* the type of the current token */
    enum TokenType type;
    /* the string value */
    char *svalue;
    /* the integer value */
    int ivalue;
    /* the proceeding token */
    struct token_T *next;
};

struct token_T *allocate_token(enum TokenType type, char *value);

struct token_T *new_token(struct token_T *token, enum TokenType type, char *value);

#endif /* TOKEN_H */
