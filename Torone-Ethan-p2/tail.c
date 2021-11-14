#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define BUFF_SIZE 1024
#define DEFAULT_LINES 10


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
    lseek(file, 1, SEEK_CUR);
    while ((rres = read(file, buffer, BUFF_SIZE)) > 0) {
        wres = 0;
        for (int i = 0; i < rres; i++) {
            wres += write(STDOUT_FILENO, buffer + wres, 1);
        }
    }

    close(file);
}


int main(int argc, char * argv[]) {

    int num = 10, type = 0, mode = 0, opt = 0;
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
            tail(num, type, mode, argv[optind]);
            optind++;
        }
    } else {
        tail(num, type, mode, STDIN_FILENO);
    }
    return EXIT_SUCCESS;

}
