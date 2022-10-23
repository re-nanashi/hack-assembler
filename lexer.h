/**
 * @file hash_table.h
 * @author re-nanashi
 * @brief Lexer public functions and data types
 */

#ifndef LEXER_H
#define LEXER_H

/* @brief Kinds of token */
typedef enum { 
    TK_RESERVED, 
    TK_ID, 
    TK_OPERATOR, 
    TK_INT, 
    TK_EOC, 
} token_kind ;

/* @brief Token struct */
struct token {
    /* the kind of the current token */
	token_kind kind;
    /* the proceeding token */
	struct token *next;
    /* the string value of the token */
	char *str;
    /* the integer value of the token if TK_INT */
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
 * @param tk_kind the current token
 * @param cur the current token
 * @param str the string to tokenize
 * @return the new allocated token's address
 */
struct token *new_token(token_kind tk_kind, struct token *cur, char *str);

/**
 * @brief Tokenize a string buffer
 *
 * @param command_buffer command string to tokenize
 * @return the new allocated token's address
 */
struct token *tokenize(char *command_buffer);

/**
 * @brief Checks whether the token is an end-of-command
 *
 * @param cur the current token
 * @return true if the current token's kind is TK_EOC
 */
bool at_eoc(struct token const *cur);

/**
 * @brief Peek the next token
 *
 * @param tok the current token
 * @return the current token's next token
 */
struct token *tk_peak(struct token const *tok);

/**
 * @brief Consume the current token
 *
 * @param tok the current token
 */
void tk_consume(struct token **tok);

/**
 * @brief Frees the token stream
 *
 * @param tok the head of token stream
 */
void free_tk_stream(struct token **tok); 

#endif /* LEXER_H */
