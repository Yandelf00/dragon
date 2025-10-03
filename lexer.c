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
	char *s;
	fp = fopen("test.txt", "r");

	if (fp == NULL){
		// printf("cannot read the file\n");
		perror("couldn't read the file\n");
		exit(1);
	} else {
		source = file_to_source(fp);
		// source->source = s;
		// source->current = &s[0];
		// source->start = &s[0];
		// source->line = 1;
		le_scan(source, token_array);
	}
	free(token_array);
	free(source->source);
	free(source);
	fclose(fp);
}

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

void le_scan(Source *source, TokenArray *token_array){
	char *t = source->source;
	size_t size = strlen(t);
	// int size = 0;
	int size_of_source = sizeof(source->source);
	
	for(int i=0; i < size; i++){
		printf("%c", t[i]);
	}
	
	// for( ; *t != '\0'; t++){
	// 	size++;
	// }
	// printf("%d\n", size);


	// printf("%d\n", size);
}



