#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char* argv[]) {
    char n = 0;
    int numLines = 10;
    char c = 0;
    int numBytes = 0;
    char * filename = argv[argc - 1];
    int fileDescriptor = open(filename, 0_RDONLY, 0644);

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



    if (n == 1) {
        for (int i = 1; i <= numLines | ; i++ ) {

        }
    } else if (c == 1) {
        for (int i = 1; i <= numBytes; i++) {

        }
    } else {

    }


    printf("n: %d; numLines: %d; c: %d; numBytes: %d\n", n, numLines, c, numBytes);
    return EXIT_SUCCESS;
}
