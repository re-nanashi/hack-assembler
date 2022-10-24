/**
 * @file parser.h
 * @author re-nanashi
 * @brief Parser public functions and data types
 */

#ifndef PARSER_H
#define PARSER_H

/* forward declaration */
struct token;

/* @brief Hack command types */
enum command_type { A_COMMAND, C_COMMAND, L_COMMAND };

/**
 * @brief Parses the asm command token stream
 *
 * @param tk_stream the token stream to parse
 * @return the command type of the asm command
 */
enum command_type parse(struct token *tk_stream);

/**
 * @brief Print the command type
 *
 * @param ct integer representation of command type enum
 * @return the command type as a string
 */
const char *print_command_type(int ct);

#endif /* PARSER_H */
