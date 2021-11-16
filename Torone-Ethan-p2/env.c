#include <stdlib.h>
#include <stdio.h>

/**
 * Iterates through all environmental variables and writes them to
 * standard output.
 */
int main(int argc, char *argv[], char * envp[]) {
    setbuf(stdout, NULL);
    for (int i = 0; envp[i] != NULL; i++)
        printf("%s\n", envp[i]);
    return 0;
}
