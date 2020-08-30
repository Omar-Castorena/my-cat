/*PROGRAM: mycat.c
 * AUTHOR: Omar Castorena
 * DESCRIPTION: This program opens the file(s) specified in the arguments and displays the contents in the terminal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int printFile(char filename[50]);

int main(int argc, char *argv[])
{
    int ret,
        i;

    char filename[50];

    // checks for correct amount of agruments
    if (argc < 2)
    {
        printf("No file names specified as arguments. Exiting now.\n");
        exit(-1);
    }

    for (i = 1; i < argc; i = i + 1)
    {

        strcpy(filename, argv[i]);

        printf("------------------------ %s ------------------------\n", filename);

        printFile(filename);

        printf("\n");
    }

    return 0;
}
// Function that opens a file, reads and prints the contents, and closes file.
int printFile(char filename[50])
{

    int readfd,
        rcount,
        bcount = 0,
        wcount = 0;

    char buffer[BUFFER_SIZE];

    // opens file and checks if any errors occurred
    readfd = open(filename, O_RDONLY, 0);
    if (readfd < 0)
    {
        printf("Unable to open file %s: %s\n", filename, strerror(errno));
    }
    else
    {
        // read/write data from file and checks for for errors
        rcount = read(readfd, buffer, BUFFER_SIZE);
        while (rcount != 0)
        {
            bcount = bcount + rcount;
            if (rcount == -1)
            {
                printf("Unable to read from file %s: Error Unknown\n", filename);
                exit(-1);
            }
            wcount = write(1, buffer, rcount);
            if (wcount == -1)
            {
                printf("Unable to write from file %s: Error Unknown\n", filename);
                exit(-1);
            }
            rcount = read(readfd, buffer, BUFFER_SIZE);
        }
        close(readfd);
    }
    return 0;
}
