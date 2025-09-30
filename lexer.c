#include "lexer.h"
#include <stddef.h>
#include <stdio.h>


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
} Source;

// here starts our lexer.
void lexer()
{
	FILE *fp;
	char *source;
	fp = fopen("text.txt", "r");

	if (fp == NULL){
		printf("cannot read the file\n");
	} else {
		// read_file(fp);
		source = read_file(fp);
	}

	fclose(fp);
}

char *read_file(FILE *fp){
	int c;
	Token t;
	TokenArray *t_array = malloc(128 * sizeof(Token));
	char *s = malloc(128 * sizeof(char));
	int i = 0;

	while((c = getc(fp)) != EOF) {
		printf("%c", c);
		s[i] = c;
		i++;
		// if(c != ' '){
		// 	printf("%c", c);
		// } else {
		// 	printf("\n");
		// }
	}
	for(int j = 0; j < i ; j++){
		printf("%c\n", s[j]);
	}
	printf("%lu\n", sizeof(s));
	return s;
}
