#include <stdio.h>
#include <stdlib.h>

void match(char c, char **pt);
void e_prime(char **pt);

void e(char **pt){
	if(**pt == 'i'){
		match('i', pt);
		e_prime(pt);
	} else {
		printf("there was a error, expected i");
	}
}

void e_prime(char **pt){
	if(**pt == '+'){
		match('+', pt);
		match('i', pt);
		e_prime(pt);
	}else {
		return;
	} 
}

void match(char c, char **pt){
	if(**pt == c){
		(*pt)++;
	} else {
		printf("expected something else");
	}
}

int main(void) {
	char test[] = "i+i+i+i+i";
	char *pt = test;
	e(&pt);
	if(*pt == '\0'){
		printf("Valid expression\n");
	} else {
		printf("it didn't work\n");
	}
  return 0;
}
