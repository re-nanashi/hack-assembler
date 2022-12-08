/**
 * @file hash_table.h
 * @author re-nanashi
 * @brief Lexer public functions and data types
 */

#ifndef LEXER_H
#define LEXER_H

/**
 * @brief Tokenize a string buffer
 *
 * @param cmd_buffer command string to tokenize
 * @return the new allocated token's address
 */
struct token *lex_tokenize(char *cmd_buffer);

/**
 * @brief Peek the next token
 *
 * @param tok the current token
 * @return the current token's next token address
 */
struct token *lex_peak(struct token const *tok);

/**
 * @brief Consume the current token
 *
 * @param tok the current token
 */
void lex_consume(struct token **tok);

/**
 * @brief Frees the token stream
 *
 * @param tok the head of token stream
 */
void lex_free_tok_stream(struct token **tok);

#endif /* LEXER_H */
