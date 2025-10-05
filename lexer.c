#include "lexer.h"
// #include <stddef.h>
#include <stdio.h>
#include <string.h>


// here starts our lexer.
void lexer()
{
	FILE *fp;
	TokenArray *token_array = malloc(sizeof(TokenArray));
	Source *source;

	initialize_token(token_array);
	fp = fopen("test.txt", "r");

	if (fp == NULL){
		perror("couldn't read the file\n");
		exit(1);
	} else {
		source = file_to_source(fp);
		scanner(source, token_array);
	}
	free_token_array(token_array);
	free(token_array);
	free(source->source);
	free(source);
	fclose(fp);
}

// This function is responsible for taking the content
// of the file and putting it in a source structure.
Source *file_to_source(FILE *fp){
	Source *src = malloc(sizeof(Source));
	int n = 128;
	int c;
	char *s = malloc(n * sizeof(char));
	int i = 0;

	while((c = getc(fp)) != EOF) {
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
	
	s[i] = '\0';

	src->source = s;
	// src->current= &s[0];
	// src->start= &s[0];
	// src->line= 0;
	src->source_size= i;

	return src;
}

// This function is responsible for scanning the source
// structure and filling the token array with tokens
void scanner(Source *source, TokenArray *token_array){
	// Token *token = malloc(sizeof(Token));
	char *src= source->source;
	int source_size = source->source_size;
	int start = 0;
	int current = 0;
	int line = 1;
	char current_char;

	while(!is_at_end(current, source_size))
	{
		start = current;
		current_char = src[current++];
		switch (current_char) {
			case '(' : {
				Token token;
				token.token_type = LEFT_BRACE;
				token.lexeme = my_stdrup("(");
				token.line = line;
				add_token(token_array, token);
				break;
			}
			case ')' : {
				Token token;
				token.token_type = RIGHT_BRACE;
				token.lexeme = my_stdrup(")");
				token.line = line;
				add_token(token_array, token);
				break;
			}
		}

	}
	// int j = 0;
	
	//TODO : implement the scan token function 
	// while(!is_at_end(source->current, source->source_size)){
	// 	printf("somehting " );
	// }

	// int j = 0;
	//
	// while(src[j] != '\0'){
	// 	printf("%c", src[j]);
	// 	j++;
	// }
}



// Helper functions here
// returns TRUE is we are at the end of the array
// returns FALSE if not
int is_at_end(int current, int length){
	return current >= length; 
}

void initialize_token(TokenArray *token_array)
{
	token_array->count = 0;
	token_array->capacity = 100;
	token_array->tokens = malloc(token_array->capacity * sizeof(Token));
}


void add_token(TokenArray *token_array, Token token)
{
	if(token_array->count >= token_array->capacity){
		token_array->capacity *= 2;
		token_array->tokens = realloc(token_array->tokens, token_array->capacity * sizeof(Token));
		if(!token_array){
			perror("couldn't allocate the tokens");
			exit(1);
		} 
	}

	printf("xxddd\n");
	token_array->tokens[token_array->count++] = token;
}

char *my_stdrup(const char *s)
{
	size_t len = strlen(s)+1;
	char *dup = malloc(len);
	if(dup) memcpy(dup, s, len);
	return dup;
}



void free_token_array(TokenArray *token_array){
	for(int i = 0; i < token_array->count; i++) {
		free(token_array->tokens[i].lexeme);
	}
	free(token_array->tokens);
}
