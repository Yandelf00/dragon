#ifndef __LEXER__
#define __LEXER__
#include <stdlib.h>
#include <stdio.h>

#define LEXEME_SIZE 20

void lexer();
char *file_to_source(FILE *fp);
void scan_token();

#endif // ndef __LEXER__
