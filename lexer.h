#ifndef __LEXER__
#define __LEXER__
#include <stdlib.h>
#include <stdio.h>

#define LEXEME_SIZE 20

// token type 
typedef enum ttype{ 
	// Single character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

	// Literals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF,
	NIL, OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	ENDF
} Ttype;

// our token structure, contains all the important 
// informations about every token.
typedef struct {
	Ttype token_type;
	char *lexeme;
	int line;
} Token;

typedef struct {
	Token *tokens;
	size_t count;
	size_t capacity;
} TokenArray;

typedef struct {
	char *source; // pointer to the source text
	int source_size;
} Source;

void lexer();
Source *file_to_source(FILE *fp);
void scanner(Source *source, TokenArray *token_array);
int is_at_end(int current, int length);
void initialize_token_array(TokenArray *token_array);
void add_token(TokenArray *token_array, Token token);
void initialize_token(Token *token, Ttype token_type, const char *s, int line);
void free_token_array(TokenArray *token_array);
char *my_stdrup(const char *s);


#endif // ndef __LEXER__
