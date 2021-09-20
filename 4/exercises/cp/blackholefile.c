#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BLACKHOLE_SIZE 1
#define BLACKHOLE_COUNT 50

int
main(int argc, char *argv[]) {
    char *targetFileName = argv[1];
    char *textToWrite = "Shine bright like a diamond!";

    int fd = open(
        targetFileName, 
        O_WRONLY | O_CREAT,
        S_IRGRP | S_IRUSR | S_IROTH |
        S_IWGRP | S_IWUSR | S_IWOTH
    );


    if (fd == -1) {
        fprintf(stderr, "Failed to open file %s\n", targetFileName);
    }


    for (int i = 0; i < BLACKHOLE_COUNT; i += 1) {
        int currentSeek = lseek(fd, BLACKHOLE_SIZE, SEEK_CUR);
        write(fd, textToWrite, strlen(textToWrite));
        fprintf(stdout, "Info:\n\t Current seek is: %d\n",currentSeek);
    }

    close(fd);

    fprintf(stdout, "Finished Black Hole file %s\n", targetFileName);
}
