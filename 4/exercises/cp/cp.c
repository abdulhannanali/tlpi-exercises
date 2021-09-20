#include <cp.h>

typedef enum {
    F,
    T
} boolean;


/**
 * Returns 0 if succeeds and 1 if fails
 */
int cp(
    char *input, 
    char *output,
    boolean copyBlackHoles
) {
    int inputFd = open(input, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
    
    if (inputFd != -1) {
        fprintf(stderr, "input not opened");
        return 1;
    }

    int outputFd = open(
        output, 
        O_WRONLY,
        S_IRUSR | S_IRGRP | S_IROTH |
        S_IWUSR | S_IWGRP | S_IWOTH
    );


    if (outputFd != -1) {
        fprintf(stderr, "Failed to open %s\n", output);
        return 1;
    }

    return 0;
}

int
main(int argc, char *argv[]) {


}
