#include "lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>


// here starts our lexer.
void lexer()
{
	FILE *fp;
	TokenArray *token_array = malloc(sizeof(TokenArray));
	Source *source;
	fp = fopen("test.txt", "r");

	if (fp == NULL){
		perror("couldn't read the file\n");
		exit(1);
	} else {
		source = file_to_source(fp);
		scanner(source, token_array);
	}
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
	src->current= &s[0];
	src->start= &s[0];
	src->line= 0;
	src->source_size= i;

	return src;
}

// This function is responsible for scanning the source
// structure and filling the token array with tokens
void scanner(Source *source, TokenArray *token_array){
	char *t = source->source;
	// size_t size = strlen(t);
	printf("%d\n", source->source_size);
	int j = 0;
	
	//TODO : implement the scan token function 
	while(t[j] != '\0'){
		printf("%c", t[j]);
		j++;
	}
}



