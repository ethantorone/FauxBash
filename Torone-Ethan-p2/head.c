#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define BUFF_SIZE 1024
#define DEFAULT_LINES 10


void head(int num, int type, int mode, char * filename) {
    //printf("%s: %d, %d, %d\n", filename, mode, type, num);
    int rres, wres, file, n = 1;
    char buffer[BUFF_SIZE];

    if (filename == NULL) {
        file = STDIN_FILENO;
    } else {
        file = open(filename, O_RDONLY);
    }

    if (mode == 'v') {
        printf("==> %s <==", filename);
    }

    while ((rres = read(file, buffer, BUFF_SIZE)) > 0 && n <= num) {
        wres = 0;
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

int main(int argc, char* argv[]) {

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
            head(num, type, mode, argv[optind]);
            optind++;
        }
    } else {
        head(num, type, mode, STDIN_FILENO);
    }
    return EXIT_SUCCESS;
}
