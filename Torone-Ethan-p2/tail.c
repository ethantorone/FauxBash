#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define BUFF_SIZE 1024
#define DEFAULT_LINES 10

/**
 * Writes the last {@code num} lines or bytes of the specified file
 * to standard output.
 *
 * @param num the number of desired lines/bytes to be printed
 * @param type determines if the function writes an amount of lines or btyes
 * @param mode determines if the function writes a banner ahead of the content
 * @param filename the name of the desired file
 */
void tail(int num, int type, int mode, char * filename) {
    //printf("%s: %d, %d, %d\n", filename, mode, type, num);
    int file, rres, wres, n = 1, offset = 1, lres;
    char buffer[BUFF_SIZE];

    if (filename == NULL) {
        file = STDIN_FILENO;
    } else if ( ( file = open(filename, O_RDONLY) ) < 1) {
        //printf("%d\n", file);
        perror("tail: cannot open file for reading");
        exit(EXIT_FAILURE);
    }

    if (mode == 'v') {
        printf("==> %s <==", filename);
    }

    num++;

    //iterates the offset backwards through the file while counting next-lines
    // or bytes; one more than desired because you want to print everything after
    // the n+1th nextline
    while ((lres = lseek(file, -1 * offset, SEEK_END)) > 0 &&
        (rres = read(file, buffer, 1)) > 0 &&
        n <= num) {
        //printf("%d\n", lres);
        for (int i = 0; i < rres && n <= num; i++) {
            if (buffer[i] == '\n' && type != 'c') {
                n++;
            } else if(type == 'c') {
                n++;
            }
        }
        offset += rres;
    }

    //you want to print everything after the n+1th nextline
    lseek(file, 1, SEEK_CUR);

    //starts reading the file from the offset and writing
    // it to standard output
    while ((rres = read(file, buffer, BUFF_SIZE)) > 0) {
        wres = 0;
        for (int i = 0; i < rres; i++) {
            wres += write(STDOUT_FILENO, buffer + wres, 1);
        }
    }

    close(file);
}


/**
 * Parses command-line arguments and calls tail() on all the files.
 */
int main(int argc, char * argv[]) {

    int num = 10, type = 0, mode = 0, opt = 0;

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
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        while (optind < argc) {
            tail(num, type, mode, argv[optind]);
            optind++;
        }
    } else {
        tail(num, type, mode, STDIN_FILENO);
    }
    return EXIT_SUCCESS;

}
