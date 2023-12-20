/* 
----------------------------------------------------------------------
Program: myRand.c
Date: October 7, 2023
Student Name & NetID: Kennedy Keyes kfk38
Description: This program generates a new file name dataX.dat where X is
a random number between 0 and 255. It then generates 60 values between 0
and 100, storing them in the file. This program exits with an exit status
of X.
----------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // random number between 0 and 255
    int random_num = rand() % 256;

    // new file with a random number between 0 and 255 for X: dataX.dat
    char filename[20];
    sprintf(filename, "data%d.dat", random_num);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 60 values between 0 and 100 generated and written to the file
    for (int i = 0; i < 60; i++) {
        int value = rand() % 101; // Generate a random value between 0 and 100
        if (write(fd, &value, sizeof(int)) == -1) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    close(fd);

    // exit status of X
    exit(random_num);
}
