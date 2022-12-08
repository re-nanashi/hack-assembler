/**
 * @file token.h
 * @author re-nanashi
 * @brief Token public functions and data types
 */

#ifdef TOKEN_H
#define TOKEN_H

/* @brief types of token */
typedef enum {
        TK_RESERVED = 1,
        TK_RESERVED_JMP,
        TK_RESERVED_DEST,
        TK_ID,
        TK_EQUALS,
        TK_OP,
        TK_A_OP,
        TK_LPAREN,
        TK_RPAREN,
        TK_SEMI,
        TK_INT,
        TK_EOC,
} token_t;

/* @brief Token struct */
struct token {
        /* type of the token */
        token_t type;
        /* the proceeding token */
        struct token *next;
        /* the string value */
        char *str;
        /* the int value if TK_INT */
        int val;
};

/**
 * @brief Allocate a token into memory
 *
 * @return the allocated token's address
 */
struct token *allocate_token(void);

/**
 * @brief Create a new token
 *
 * @param tk_type the current token
 * @param cur_tk the current token
 * @param str the string to tokenize
 * @return the new allocated token's address
 */
struct token *new_token(token_t tok_type, struct token *cur_tok, char *str);

#endif /* TOKEN_H */
