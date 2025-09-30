#ifndef __LEXER__
#define __LEXER__
#include <stdlib.h>
#include <stdio.h>

#define LEXEME_SIZE 20

void lexer();
char *read_file(FILE *fp);

#endif // ndef __LEXER__
