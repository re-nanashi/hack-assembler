/**
 * @file hash_table.h
 * @author re-nanashi
 * @brief Lexer public functions and data types
 */

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"

typedef struct LEXER_STRUCT
{
    char *src;
    size_t src_size;
    char c;
    unsigned int i;
} lexer_T;

lexer_T *init_lexer(char *src);

void lexer_advance(lexer_T *lexer);

void lexer_skip_whitespace(lexer_T *lexer);

token_T *lexer_next_token(lexer_T *lexer);

#endif /* LEXER_H */
