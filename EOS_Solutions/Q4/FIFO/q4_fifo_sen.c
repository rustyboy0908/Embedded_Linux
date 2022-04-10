#include<stdio.h>
#include<string.h>
#include <unistd.h> // for implementig fifo(named pipes)
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h> 
#include<errno.h>
#include <sys/types.h>  //headers used for open API
#include <sys/stat.h>


int main(int argc, const char * argv[])
{
    int pd;
    FILE* fd;
    unsigned char buffer[100];  
    
    fd=fopen("/home/ubuntu/Documents/EOS_allSOLUTION/Q4/FIFO/dictionary.txt","r");
    if(fd == NULL)
    {
        perror("Error-->");
        return 0;
    }
    // opening of the file discriptor with write only permission i.e O_WRONLY
    pd = open("desdfifo",O_WRONLY);
    if(pd == -1)
    {
        perror("Error");
        return 0;
    }
    while(fgets(buffer,100,fd) != NULL)
    {
        if(buffer[0]=='m')
        {
            write(pd,buffer,100);
            printf("Sending Data %s",buffer);
        }
    }
    close(pd);
    fclose(fd);
    return 0;
}