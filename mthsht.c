#include "mthsht.h"

void e(char **el)
{
  if(**el == 'i'){
    match(**el, 'i');
    (*el)++;
    e_prime(**el);
  }
}

void e_prime(char **el){

}

int main(void) {
  char text[] = "i+i";
  char *ptr = &text[0];
  e(&ptr);

  return 0;
}
