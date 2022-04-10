//Passing on the fileter words from dictionary to child Process from parents via Pipe IPC method.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd[2];
    int i;
    FILE *fp; // file discriptor pointer
    unsigned char buffer[100];
    unsigned char child_buff[100];
    // create pipe descriptors
    if(pipe(fd)== -1)
    {
        perror("Error");
        return 0;
    }

    fp = fopen("/home/ubuntu/Documents/EOS_allSOLUTION/Q4/dictionary.txt", "r");
    if (fp == NULL)
    {
        perror("Error");
        return 0;
    }
    else
        printf("File opening successfull !\n");

    // fork() returns 0 for child process, child-pid for parent process.
    if (fork() != 0)
    {
        // parent: writing only, so close read-descriptor.
        close(fd[0]);
        printf("Parent Process running!\n");
        // send the value on the write-descriptor.
        while (fgets(buffer, 100, fp) != NULL)
        {
            if (buffer[0] == 'm')
            {
                write(fd[1], buffer, sizeof(buffer));
                printf("Parent(%d) send value: %s\n", getpid(), buffer);
            }
        }
        //printf("%s",child_buff);
        printf("Parent Process Ends here\n");
        // close the write descriptor
        close(fd[1]);
    }
    else
    { // child: reading only, so close the write-descriptor
        close(fd[1]);
        printf("Child Process Started!!");
        // now read the data (will block)
        while(i<100)
        {
        read(fd[0], child_buff, sizeof(child_buff));
        printf("Child(%d) received value: %s\n", getpid(),child_buff);
        i++;
        }
        // close the read-descriptor
        close(fd[0]);
    }
    return 0;
}