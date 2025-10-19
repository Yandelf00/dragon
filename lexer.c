#include "lexer.h"
#include <stdio.h>
#include <string.h>


// here starts our lexer.
void lexer()
{
	FILE *fp;
	TokenArray *token_array = malloc(sizeof(TokenArray));
	Source *source;

	initialize_token_array(token_array);
	fp = fopen("test.txt", "r");

	if (fp == NULL){
		perror("couldn't read the file\n");
		exit(1);
	} else {
		source = file_to_source(fp);
		scanner(source, token_array);
	}

	for(int x=0; x < token_array->count; x++) {
		printf("%u\n", token_array->tokens[x].token_type);
	}

	//this actually is going to free
	//the content of token_array
	free_token_array(token_array); 
	//this frees token_array
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
	src->source_size = i;

	return src;
}

// This function is responsible for scanning the source
// structure and filling the token array with tokens
void scanner(Source *source, TokenArray *token_array){
	char *src= source->source;
	int source_size = source->source_size;
	int start = 0;
	int current = 0;
	int line = 1;
	char current_char;

	while(current < source_size)
	{
		start = current;
		current_char = src[current++];//sets the current char then adds one to current
		switch (current_char) {
			case '(' : {
				token_to_array(token_array, LEFT_PAREN, "(", line);
				break;
			}
			case ')' : {
				token_to_array(token_array, RIGHT_PAREN, ")", line);
				break;
			}
			case '{' : {
				token_to_array(token_array, LEFT_BRACE, "{", line);
				break;
			}
			case '}' : {
				token_to_array(token_array, RIGHT_BRACE, "}", line);
				break;
			}
			case ',' : {
				token_to_array(token_array, COMMA, ",", line);
				break;
			}
			case '.' : {
				token_to_array(token_array, DOT, ".", line);
				break;
			}
			case '-' : {
				token_to_array(token_array, MINUS, "-", line);
				break;
			}
			case '+' : {
				token_to_array(token_array, PLUS, "+", line);
				break;
			}
			case ';' : {
				token_to_array(token_array, SEMICOLON, ";", line);
				break;
			}
			case '*' : {
				token_to_array(token_array, STAR, "*", line);
				break;
			}
			case '!' : {
				if(src[current] == '=') {
					token_to_array(token_array, BANG_EQUAL, "!=", line);
					current++;
				} else {
					token_to_array(token_array, BANG, "!", line);
				}
				break;
			}
			case '=' : {
				if(src[current] == '=') {
					token_to_array(token_array, EQUAL_EQUAL, "==", line);
					current++;
				} else {
					token_to_array(token_array, EQUAL, "=", line);
				}
				break;
			}
			case '<' : {
				if(src[current] == '=') {
					token_to_array(token_array, LESS_EQUAL, "<=", line);
					current++;
				} else {
					token_to_array(token_array, LESS, "<", line);
				}
				break;
			}
			case '>' : {
				if(src[current] == '=') {
					token_to_array(token_array, GREATER_EQUAL, ">=", line);
					current++;
				} else {
					token_to_array(token_array, GREATER, ">", line);
				}
				break;
			}
			case '/' : {
				if(src[current] == '/') {
					while (src[current] != '\n' && current < source_size) {
						current++;
					}
				} else {
					token_to_array(token_array, SLASH, "/", line); 
				}
				break;
			}
			case ' ': break;
			case '\r': break;
			case '\t': break;
			case '\n' : {
				line++;
				break;
			}
			case '"' : {
				int cmpt = 0;
				char *holder;
				while(src[current] != '"' && current < source_size){
					if(src[current] == '\n') {
						line++;
					}
					current++;
					cmpt++;
				}

				if(current >= source_size){
					perror("Unterminated string.");
					exit(1);
				}

				current++;

				holder = malloc(sizeof(char) * cmpt);
				for(int i = 0; i < cmpt; i++) {
					holder[i] = src[start+i+1];
				}

				token_to_array(token_array, STRING, holder, line); 
				free(holder);
				break;
			}

			default:{
				int cmpt = 0;
				char *holder;
				if(current_char >= '0' && current_char <= '9'){
					while(src[current] >= '0' && src[current] <= '9'){
						current++;
						cmpt++;
					}
					holder = malloc(sizeof(char) * cmpt);
					for(int i = 0; i <= cmpt; i++) {
						holder[i] = src[start + i];
					}
					token_to_array(token_array, NUMBER, holder, line); 
					free(holder);
				} else if (is_alpha(current_char)) {
					while(is_alpha_numerical(src[current])){
						current++;
						cmpt++;
					}
					holder = malloc(sizeof(char) * cmpt);
					for(int i = 0; i <= cmpt; i++) {
						holder[i] = src[start + i];
					}
					if(strcmp("or", holder) == 0){
						token_to_array(token_array, OR, holder, line); 
					} else if (strcmp("if", holder) == 0){
						token_to_array(token_array, IF, holder, line); 
					} else if (strcmp("else", holder) == 0){
						token_to_array(token_array, ELSE, holder, line); 
					} else if (strcmp("and", holder) == 0){
						token_to_array(token_array, AND, holder, line); 
					} else if (strcmp("false", holder) == 0){
						token_to_array(token_array, FALSE, holder, line); 
					} else if (strcmp("true", holder) == 0){
						token_to_array(token_array, TRUE, holder, line); 
					} else if (strcmp("while", holder) == 0){
						token_to_array(token_array, WHILE, holder, line); 
					} 
					free(holder);
				} else {
					fprintf(stderr, "Unexpected character: %c\n", current_char);
					exit(1);
				}
				break;
			}
		}
	}
}


// ----------------Helper functions----------------
//
// returns TRUE(1) is we are at the end of the array
// returns FALSE(0) if not
int is_at_end(int current, int length){
	return current >= length; 
}

// This function's purpose is to initialize the 
// token array that gonna contain all our tokens
void initialize_token_array(TokenArray *token_array)
{
	token_array->count = 0;
	token_array->capacity = 100;
	token_array->tokens = malloc(token_array->capacity * sizeof(Token));
}

// This functions's purpose is to initialize our tokens,
// we need to provide informations such as token type, lexeme
// and line.
void initialize_token(Token *token, Ttype token_type, const char *s, int line)
{
	token->token_type = token_type;
	token->lexeme = my_stdrup(s);
	token->line = line;
}

// This function's purpose is to add our token to our token
// array
void add_token_to_array(TokenArray *token_array, Token token)
{
	if(token_array->count >= token_array->capacity){
		token_array->capacity *= 2;
		token_array->tokens = realloc(token_array->tokens, token_array->capacity * sizeof(Token));
		if(!token_array){
			perror("couldn't allocate the tokens");
			exit(1);
		} 
	}

	token_array->tokens[token_array->count++] = token;
}

// This function is a helper function that basically takes care
// of the initialization of our token and then adding it to the token
// array.
void token_to_array(TokenArray *token_array, Ttype token_type, const char *s, int line)
{
	Token token;
	initialize_token(&token, token_type, s, line);
	add_token_to_array(token_array, token);
}


// This function's purpose is to make a copy of a string
// so that i can keep using that string even if it's freed.
// If i don't use it, then my token arrays will point at a
// certain character, but once its freed i will have no lexeme
// in my token. This function is used in the initialize_token 
// function.
char *my_stdrup(const char *s)
{
	size_t len = strlen(s)+1;
	char *dup = malloc(len);
	if(dup) memcpy(dup, s, len);
	return dup;
}

// This function takes care of freeing our token array
// avoiding memory leaks
void free_token_array(TokenArray *token_array){
	for(int i = 0; i < token_array->count; i++) {
		printf("freeing the lexeme %s\n", token_array->tokens[i].lexeme);
		free(token_array->tokens[i].lexeme);
	}
	free(token_array->tokens);
}

int is_alpha(char cc){
	return (cc >= 'a' && cc<='z') || (cc >= 'A' && cc <= 'Z') || cc == '_';
}

int is_alpha_numerical(char cc) {
	return is_alpha(cc) || (cc >= '0' && cc <= '9');
}






