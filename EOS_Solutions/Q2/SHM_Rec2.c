#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define SIZE 512
int *count; //pointer to the shared memory.
int num;
unsigned char* pass_dictionary;
int main()
{
    int shmd;
    //opening the shared memory.
    shmd= shm_open("/shm_dictionary",O_RDWR| O_CREAT,S_IRUSR | S_IWUSR);
    //trunkating the size of shared memory.
    ftruncate(shmd,SIZE); 
    //mmap will return pointer pointing to the shared memory   
    pass_dictionary= (char*)mmap(NULL,SIZE,PROT_READ | PROT_WRITE, MAP_SHARED,shmd,0);
    
    printf("Mesg Rec:\n%s",pass_dictionary);
    return 0;
}