#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 1024
#define DEFAULT_LINES 10

/**
 * Writes the first {@code num} lines or bytes of the specified file
 * to standard output.
 *
 * @param num the number of desired lines/bytes to be printed
 * @param type determines if the function writes an amount of lines or btyes
 * @param mode determines if the function writes a banner ahead of the content
 * @param filename the name of the desired file
 */
void head(int num, int type, int mode, char * filename) {
    //printf("%s: %d, %d, %d\n", filename, mode, type, num);
    int rres, wres, file, n = 1;
    char buffer[BUFF_SIZE];

    //if no filename is passed, then program reads from standard input
    if (filename == NULL) {
        file = STDIN_FILENO;
    } else if ( ( file = open(filename, O_RDONLY) ) < 1) {
        //printf("%d\n", file);
        //if there's an error with opening the file, then program stops
        perror("head: cannot open file for reading");
        exit(EXIT_FAILURE);
    }

    if (mode == 'v') {
        printf("==> %s <==", filename);
    }

    //repeatedly reads the file, stops if there is no more content to read or
    //if specified number of lines/bytes have been written
    while ((rres = read(file, buffer, BUFF_SIZE)) > 0 && n <= num) {
        wres = 0;
        //writes byte-by-byte to standard output until whats read into the buffer
        //has been written or if the specified number of lines/bytes has been written
        for (int i = 0; (i < rres) && n <= num; i++) {
            wres += write(STDOUT_FILENO, buffer + wres, 1);
            if (buffer[i] == '\n' && type != 'c') {
                n++;
            } else if (type == 'c') {
                n++;
            }
        }
    }
    close(file);
}


/**
 * Parses command-line arguments and calls head() on all the files.
 *
 * @param argc argument count
 * @param argv arguments
 */
int main(int argc, char* argv[]) {

    int num = DEFAULT_LINES, type = 0, mode = 0, opt = 0;

    //parses options and arguments
    while ((opt = getopt(argc, argv, "n:c:vq")) != -1) {
        //printf("%d\n", opt);
        switch (opt) {
        case 'n':
            num = atoi(optarg);
            type = 'n';
            //printf("%c: %d or %s\n", type, num, argv[optind]);
            break;
        case 'c':
            num = atoi(optarg);
            type = 'c';
            //printf("%c: %d or %s\n", type, num, argv[optind]);
            break;
        case 'v':
            mode = 'v';
            break;
        case 'q':
            mode = 'q';
            break;
        case '?':
            perror("invalid option\n");
            exit(1);
            break;

        } //switch
        //printf("%d: %d or %s\n\n",optind, opt, optarg);
        opt = 0;
    } //while
    //printf("%c: %d\n", type, num);

    if (num < 0) {
        perror("invalid argument: negative\n");
        exit(2);
    }

    if (optind < argc) {
        while (optind < argc) {
            head(num, type, mode, argv[optind]);
            optind++;
        }
    } else {
        head(num, type, mode, STDIN_FILENO);
    }
    return EXIT_SUCCESS;
}
