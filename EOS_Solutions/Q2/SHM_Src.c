#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SIZE 512
int * count; //pointer to the shared memory.
unsigned char dictionary[100]={'\0'};

int num;
int main()
{
    int shmd;
    FILE *fd; // File Discriptor pointer
    unsigned char* pass_dictionary;
    fd = fopen("/home/ubuntu/Documents/EOS_allSOLUTION/Q2/dictionary.txt","r");
    if(fd==NULL)
    {
        perror("Error");
        return 0;
    }
    else
    printf("Successfully Opened the dictionary file!\n");
    //opening the shared memory.
    shmd= shm_open("/shm_dictionary",O_RDWR | O_CREAT,S_IRUSR | S_IWUSR);
    if(shmd == -1)
    {
        perror("Error");
        return 0;
    }
    else
    {
        printf("Successfully Opened Shared Memory!\n");
    }
    //trunkating the size of shared memory.
    ftruncate(shmd,SIZE); 
    //mmap will return pointer pointing to the shared memory   
    pass_dictionary = (char*)mmap(NULL,SIZE,PROT_READ | PROT_WRITE, MAP_SHARED,shmd,0);
    while(fgets(dictionary,100,fd)!=NULL)
    {
       if(dictionary[0]=='m')
       {
           pass_dictionary=dictionary;
           printf("DATA%s",pass_dictionary);
       }
    }
    
    fclose(fd);
    return 0;
}