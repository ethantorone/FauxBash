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

/**
 * Returns the number of lines in a string by counting next-line characters
 *
 * @param str a string
 * @return number of lines
 */
int lineCount(char * str) {
    int lines = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            lines += 1;
        }
    }
    return lines;
}

/**
 * Returns the number of words in a string by counting whitespace without
 * counting continuous whitespaces.
 *
 * @param str a string
 * @return number of words
 */
int wordCount(char * str) {
    int words = 0, i = 0;
    // skip initial white space characters
    while (i < strlen(str)) {
        if ( str[i] == ' ' || str[i] == '\n' || str[i]== '\r' || str[i] == '\t' ||
        str[i] == '*' || str[i] == '\\' || str[i] == '/') {
            i++;
        } else {
            break;
        }
    }
    for (; i < strlen(str); i++) {
        if ( str[i] == ' ' || str[i] == '\n' || str[i]== '\r' || str[i] == '\t') {
            words+=1;
            // skip consecutive white space
            while(str[i]==' ' || str[i] == '\n' || str[i]== '\r' || str[i] == '\t') {
                i++;
            }
        }
    }
    return words;
}

/**
 * Returns the number of bytes in a string
 *
 * @param str a string
 * @return number of bytes
 */
int byteCount(char * str) {
    return strlen(str);
}

/**
 * Prints a desired combination of byte, word, and line counts of desired files.
 * Mode is calculated in calling function by using bitwise or on predefined constants
 * at the top of the file.
 *
 * @param filename name of desired file
 * @param mode byte | word | line
 */
void wc(int mode, char * filename) {
    //printf("%s: %d\n", filename, mode);
    int file = open(filename, O_RDONLY);
    char buffer[BUFF_SIZE];
    int words = 0, lines = 0, bytes = 0, rres = 0;

    //reads the file into the buffer and passes the string to all
    //the counting functions
    while ((rres = read(file, buffer, BUFF_SIZE)) > 0) {

        if (rres < BUFF_SIZE) {
            buffer[rres] = '\0';
        }

        words += wordCount(buffer);
        lines += lineCount(buffer);
        bytes += byteCount(buffer);
    }
    totalLines += lines;
    totalWords += words;
    totalBytes += bytes;

    //use bitwise and to check what options are turned on
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

/**
 * Parses command-line arguments and calls wc() on all the files.
 *
 * @param argc argument count
 * @param argv arguments
 */
int main (int argc, char * argv[]) {
    setbuf(stdout, NULL);

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

    //if there are more than 2 files, turn total counter on
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

    //totalcounter
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
