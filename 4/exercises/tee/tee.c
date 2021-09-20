/**
 * Author: Hannan Ali
 * Email: ali.abdulhannan@gmail.com
 */

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>

#define BUF_SIZE 100

/**
 * tee command
 * 
 **/
void tee(char *input, char *output, int isAppend) {
    mode_t fileAccessMode = O_RDWR | O_CREAT;
    
    int permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;


    int inputFd = open(
        input,
        O_RDONLY,
        permissions
    );

    if (inputFd == -1) {
        fprintf(stderr, "Unable to read %s ", input);
        exit(1);
    }

    if (isAppend == 1) {
        fileAccessMode = fileAccessMode | O_APPEND;
    }

    int outputFd = open(
        output,
        fileAccessMode, 
        permissions
    );


    if (outputFd == -1) {
        fprintf("Unable to write to %s", output);
        exit(1);
    }

    int numRead;
    char buf[BUF_SIZE + 1];

    while((numRead = (read(inputFd, buf, BUF_SIZE))) > 0) {
        buf[numRead] = '\0';
        printf("%s", buf);
        write(outputFd, buf, numRead);
    }

    close(inputFd);
    close(outputFd);
}

int getAppendArgument (int argc, char **argv) {
    int c;

    while ((c = getopt(argc, argv, "a")) != -1) {
        if (c == 'a') {
            return 1;
        }
    }

    return 0;
}

int
main (int argc, char **argv) {
    int appendArgument = getAppendArgument(argc, argv);

    if ((argc - optind) < 2) {
        fprintf(stderr, "Usage: \n\t tee [-a] [input] [output]\n");
        exit(1);
    }

    char *input = argv[optind];
    char *output = argv[optind + 1];

    tee(input, output, appendArgument);
}