#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define BUFF_SIZE 1024
#define DEFAULT_LINES 10

void headLine(int num, char * filename) {
    printf("headLine: %d, %s\n", num, filename);
    char buffer[BUFF_SIZE];

}

void headByte(int num, char * filename) {
    printf("headByte: %d, %s\n", num, filename);
    char buffer[BUFF_SIZE];
    int file = open(filename, O_RDONLY, 0644);
    int wres = 1, wsum = 0;;

    read(file, buffer, BUFF_SIZE);
    for (int i = 1; (i <= num) & (wres == 1); i++) {
        write(STDOUT_FILENO, buffer + wsum, 1);
        wsum += 1;
        //printf("%d: %d", i, rres);
    } //for
    //puts(buffer);

}

void headIn(int num, char * filename) {
    printf("headIn: %d, %s\n", num, filename);
    char buffer[BUFF_SIZE];

}

int main(int argc, char* argv[]) {


    int num = 0, type = 0, opt = 0;

    char * filename;

    while ((opt = getopt(argc, argv, "n:c:")) != -1) {
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

        case '?':
            filename = optarg;
            puts(filename);
            break;

        } //switch
        //printf("%d: %d or %s\n\n",optind, opt, optarg);
        opt = 0;
    } //while
    //printf("%c: %d\n", type, num);

    if (optind < argc) {
        while (optind < argc) {

            switch (type) {
            case 'n':
                headLine(num, argv[optind]);
                break;
            case 'c':
                headByte(num, argv[optind]);
                break;

            case 0:
                headLine(DEFAULT_LINES, argv[optind]);
                break;
            }
            optind++;
        }
    } else {
        switch (type) {
        case 'n':
            headLine(num, argv[optind]);
            break;
        case 'c':
            headByte(num, argv[optind]);
            break;

        case 0:
            headLine(DEFAULT_LINES, argv[optind]);
        }
        headIn(num, argv[optind]);
    }
    return EXIT_SUCCESS;







/*
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
    */
}
