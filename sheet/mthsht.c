#include "mthsht.h"

void e(char **el)
{
  if(**el == 'i'){
    match(el, 'i');
    e_prime(el);
  }
}

void e_prime(char **el){
  if(**el == '+'){
    match(el, '+');
    match(el, 'i');
    e_prime(el);
  } else {
    return;
  }
}

void match(char **el, char c) {
  if(**el == c){
    (*el)++;
  }else{
    fprintf(stderr, "Syntax error: expected '%c' but found '%c'\n", c, **el);
    exit(1);
  }
}

int main(void) {
  char text[] = "i+i+i+i+$";
  char *ptr = &text[0];
  char main = 'c';
  e(&ptr);
  if(*ptr == '$'){
    printf("parsing done\n");
  }

  return 0;
}
