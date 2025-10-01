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
	TokenArray *token_array;
	Source *source;
	char *s;
	fp = fopen("text.txt", "r");

	if (fp == NULL){
		// printf("cannot read the file\n");
		perror("couldn't read the file\n");
		exit(1);
	} else {
		s = file_to_source(fp);
		source->source = s;
		source->current = &s[0];
		source->start = &s[0];
		source->line = 1;
	}

	fclose(fp);
}

char *file_to_source(FILE *fp){
	int n = 128;
	int c;
	char *s = malloc(n * sizeof(char));
	int i = 0;

	while((c = getc(fp)) != EOF) {
		printf("%c", c);
		if(i >= n){
			n = i + 128;
			char *b = realloc(s, n*sizeof(char));
			if(!b){
				perror("error reallocating");
				exit(1);
			}
			s = b;
		}
		s[i] = c;
		i++;
	}
	
	return s;
}

void scan_token(Source *source, TokenArray *token_array){
	
}



