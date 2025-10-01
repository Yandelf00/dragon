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
	char lexeme[LEXEME_SIZE];
	int line;
} Token;

typedef struct {
	Token *data;
	size_t count;
	size_t capacity;
} TokenArray;

typedef struct {
	char *source; // pointer to the source text
	char *current; // pointer to the current character of the string 
	char *start; // point to the character in the start of the string
	int line; // current line we are in
	int source_size;
} Source;

void lexer();
Source *file_to_source(FILE *fp);
void le_scan(Source *source, TokenArray *token_array);


#endif // ndef __LEXER__
