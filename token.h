/**
 * @file token.h
 * @author re-nanashi
 * @brief Token public functions and data types
 */

#ifndef TOKEN_H
#define TOKEN_H

/* @brief types of token */
typedef enum {
        TOKEN_RES = 1,
        TOKEN_RES_JMP,
        TOKEN_RES_DEST,
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_A_OP,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_SEMI,
        TOKEN_OP,
        TOKEN_INT,
        TOKEN_EOC,
} token_type_t;

/* @brief Token struct */
struct token {
        /* type of the token */
        token_type_t type;
        /* the proceeding token */
        struct token *next;
        /* the string value */
        char *str;
        /* the int value if TOKEN_INT */
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
 * @param tok_type the current token
 * @param cur_tok the current token
 * @param str the string to tokenize
 * @return the new allocated token's address
 */
struct token *new_token(token_type_t tok_type,
                        struct token *cur_tok,
                        char *str);

/**
 * @brief Checks whether the token is an end-of-command
 *
 * @param cur_tok the current token
 * @return true if the current token's kind is TOKEN_EOC
 */
bool token_is_eoc(struct token const *cur_tok);

#endif /* TOKEN_H */
