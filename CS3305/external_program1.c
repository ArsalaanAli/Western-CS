#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{

    int R = atoi(argv[0]);
    int sum = (R * (R + 1)) / 2;
    printf("child (PID %d): external_program1:  sum: [1 - %d] = %d\n", getpid(), R, sum);
    return 0;
}
