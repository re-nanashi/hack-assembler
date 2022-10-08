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
    TK_EOF, 
} token_kind ;

/* @brief Token struct */
struct token {
	token_kind kind;
	struct token *next;
	char *str;
	int val;
};

/**
 * @brief Checks whether the token is an end-of-command
 *
 * @param cur the current token
 * @return true if the current token's kind is TK_EOC
 */
bool at_eoc(struct token const *cur);

/**
 * @brief Checks whether the token is an end-of-file
 *
 * @param cur the current token
 * @return true if the current token's kind is TK_EOF
 */
bool at_eof(struct token const *cur);

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
 * @brief Peek the next token's kind
 *
 * @param tok the current token
 * @return the current token's next token's kind
 */
token_kind peak(struct token const *tok);

/**
 * @brief Consume the current token
 *
 * @param tok the current token
 */
void consume(struct token *tok);

#endif /* LEXER_H */
