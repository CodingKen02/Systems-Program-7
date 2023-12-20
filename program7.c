/* 
----------------------------------------------------------------------
Program: program7.c
Date: October 7, 2023
Student Name & NetID: Kennedy Keyes kfk38
Description: This program uses fork to create a child process and uses
one of the exec functions to run the myRand program. Then it opens the
dataX.dat file where X is the number returned from the system. Lastly,
it reads the 60 values from the file, displays them, computes their average,
and outputs the average. It unlinks the data file for the next dataset.
----------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    pid_t child_pid;
    int status;
    int total = 0;
    int value, count = 0;

    // child process using fork
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // execute the myRand program using exec
        char *program_name = "./myRand";
        char *program_args[] = {program_name, NULL};

        if (execvp(program_name, program_args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // wait for the child to exit and get its exit status
        if (wait(&status) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        // extract the X value from the exit status
        int random_num = WEXITSTATUS(status);

        // create the filename dataX.dat
        char filename[20];
        sprintf(filename, "data%d.dat", random_num);

        // open the file for reading
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // read the 60 values from the file and display them
        printf("Values from %s:\n", filename);
        while (read(fd, &value, sizeof(int)) > 0) {
            printf("%d ", value);
            total += value;
            count++;
        }

        // compute and output the average
        if (count > 0) {
            double average = (double)total / count;
            printf("\nAverage: %.2lf\n", average);
        } else {
            printf("\nNo values found in the file.\n");
        }

        // close and unlink the data file
        close(fd);
        unlink(filename);
    }

    return EXIT_SUCCESS;
}
