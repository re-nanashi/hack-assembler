
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
