#ifndef __STRUCTS__
#define __STRUCTS__

#define LEXEME_SIZE 20

// token type 
typedef enum ttype{ 
	// Single character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
  COLON,

	// One or two character tokens.
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

	// Literals.
	IDENTIFIER, STRING_LITERAL, NUMBER,

	// Keywords.
	ELSE, FALSE, FUNCTION, FOR, IF, PRINT, RETURN, TRUE, 
  WHILE, CHAR, STRING, BOOLEAN, INTEGER, ARRAY, VOID,

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



#endif
