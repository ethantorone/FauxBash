#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define CH 4
#define LI 2
#define WO 1
#define ALL 7

#define BUFF_SIZE 1024

int totalLines = 0, totalWords = 0, totalBytes = 0;


int lineCount(char * str) {
    int lines = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            lines += 1;
        }
    }
    return lines;
}

int wordCount(char * str) {
    int words = 0, i = 0;
    // skip initial white space characters
    while (str[i] != '\0') {
        if ( str[i] == ' ' || str[i] == '\n' || str[i]== '\r' || str[i] == '\t') {
                i++;
            } else {
                break;
            }
        }
        for (; str[i] != '\0'; i++){
            if ( str[i] == ' ' || str[i] == '\n' || str[i]== '\r' || str[i] == '\t' ) {
                words+=1;
                // skip consucative white space
                while(str[i]==' ' || str[i] == '\n' || str[i]== '\r' || str[i] == '\t') {
                    i++;
                }
            }
        }
        return words;
}

int byteCount(char * str) {
    return strlen(str);
}

void wc(int mode, char * filename) {
    //printf("%s: %d\n", filename, mode);
    int file = open(filename, O_RDONLY);
    char buffer[BUFF_SIZE];
    int words = 0, lines = 0, bytes = 0, rres = 0;
    while ((rres = read(file, buffer, BUFF_SIZE)) > 0) {
        words += wordCount(buffer);
        lines += lineCount(buffer);
        bytes += byteCount(buffer);
    }
    totalLines += lines;
    totalWords += words;
    totalBytes += bytes;

    if ((mode & LI) == LI) {
        printf("%d\t", lines);
    }
    if ((mode & WO) == WO) {
        printf("%d\t", words);
    }
    if ((mode & CH) == CH) {
        printf("%d\t", bytes);
    }
    printf("%s\n", filename);
    close(file);
}


int main (int argc, char * argv[]) {
    int opt = 0, mode = 7; char total;
    while ((opt = getopt(argc, argv, "clw")) != -1) {
        switch (opt) {
        case 'c':
            if (mode == ALL) {
                mode = CH;
            } else {
                mode = mode | CH;
            }
            break;
        case 'l':
            if (mode == ALL) {
                mode = LI;
            } else {
                mode = mode | LI;
            }
            break;
        case 'w':
            if (mode == ALL) {
                mode = WO;
            } else {
                mode = mode | WO;
            }
            break;
        case '?':
            perror("invalid argument\n");
            exit(1);
        } //switch
    } //while
    if ((argc - optind) >= 2) {
        total = 1;
    }
    if (optind < argc) {
        while (optind < argc) {
            wc(mode, argv[optind]);
            optind++;
        }
    } else {
        wc(mode, STDIN_FILENO);
    }

    if (total == 1) {
        if ((mode & LI) == LI) {
            printf("%d\t", totalLines);
        }
        if ((mode & WO) == WO) {
            printf("%d\t", totalWords);
        }
        if ((mode & CH) == CH) {
            printf("%d\t", totalBytes);
        }
        printf("total\n");
    }
} //main
