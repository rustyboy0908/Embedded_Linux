#include<stdio.h>
#include<string.h>
#include <unistd.h> // for implementig fifo(named pipes)
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h> 
#include<errno.h>
#include <sys/types.h>  //headers used for open API
#include <sys/stat.h>

int main(int argc, const char* argv[])
{
    int pd;
    int i=0;
    unsigned char rbuff[100];
    pd = open("desdfifo",O_RDONLY);
    if(pd == -1)
    {
        perror("Error");
        return 0;
    }
    while(i<10)
    {
        read(pd,rbuff,100);
        printf("Received data --> %s\n",rbuff);
        i++;
    }
    close(pd);
}