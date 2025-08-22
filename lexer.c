#include "lexer.h"


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

typedef struct token{
	Ttype token_type;
	char lexeme[LEXEME_SIZE];

} Token;

void lexer()
{
	FILE *fp;
	fp = fopen("text.txt", "r");

	if (fp == NULL){
		printf("cannot read the file\n");
	} else {
		read_file(fp);
	}
}

void read_file(FILE *fp){
	int c;
	while((c = getc(fp)) != EOF) {
		printf("%c\n", c);
	}
}
