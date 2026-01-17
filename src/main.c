#include "lexer.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int c;
	TokenArray *token_array = malloc(sizeof(TokenArray));
	token_array = lexer();

	scanf("%d", &c);

	return 0;
}

