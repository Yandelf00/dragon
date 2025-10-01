#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Starting program...\n");

    // Allocate memory but never free it (leak)
    char *leak = malloc(100);

    // Write something into it so the compiler doesn’t optimize it away
    for (int i = 0; i < 99; i++) {
        leak[i] = 'A';
    }
    leak[99] = '\0';

    printf("Allocated string: %s\n", leak);

    // Intentionally forget to free(leak);
    // free(leak);  <-- if you uncomment this, leak disappears

    return 0;
}
