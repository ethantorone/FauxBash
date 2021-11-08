#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[]) {
    char n = 0;
    int numLines = 10;
    char c = 0;
    int numBytes = 0;

    char * filename = argv[argc - 1];
    int file = open(filename, O_RDONLY, 0644);
    if (file == -1) {
        file = STDIN_FILENO;
    }

    char buffer[BUFF_SIZE];

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'n') {
                n = 1;
                numLines = atoi(argv[i + 1]);
            } //if
            if (argv[i][1] == 'c') {
                c = 1;
                numBytes = atoi(argv[i + 1]);
            } //if
        } //if
    } //for

    int rres;
    int wres = 0;
    int buffLength;

    if (n == 1) {

        for (int i = 0; (i < numLines) & (wres <= buffLength); i++) {

            read(file, buffer, BUFF_SIZE);
            buffLength = strlen(buffer);
            wres = 0;
            while (wres < buffLength) {
                wres += write(STDOUT_FILENO, buffer + wres, 1);
                if (!(buffer[wres] == '\n')) {
                    i--;
                }
            }
        }
    } else if (c == 1) {
        read(file, buffer, BUFF_SIZE);
        buffLength = strlen(buffer);
        for (int i = 1; i <= numBytes; i++) {

        }
    } else {

    }


    printf("n: %d; numLines: %d; c: %d; numBytes: %d\n", n, numLines, c, numBytes);
    return EXIT_SUCCESS;
}
