#include <fcntl.h>        
#include <sys/stat.h>        
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>

mqd_t mq;
struct mq_attr rishabh_attr ;

int mq_status ;
int main()
{
  
   FILE* fd;

   //struct mq_attr rishabh_attr ;
   //int mq_status;

   rishabh_attr.mq_flags=0;
   rishabh_attr.mq_maxmsg=10;
   rishabh_attr.mq_msgsize=100;
   rishabh_attr.mq_curmsgs=0;

   char str[100]={'\0'};
   char buff[100]={'\0'};
   printf("Before opening file!\n");
   fd = fopen("dictionary.txt","r");
   //fd = fopen("/home/ubuntu/Documents/LINUX_DICTIONARY.txt","r");
   if(fd == NULL)
   {
      printf("ERROR LOADING File!");
      return 0;
   }
   else
   {
       printf("Successfully loaded mQ");
   }

   mq= mq_open("/JMD8",O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR, &rishabh_attr);
   if(mq == -1)
   {
   perror("Error");
   return 0 ;
   }
   else
   {
      printf("Message queue opened successfully!");
   }
   int i =0;
   while((fgets(buff,100,fd) != NULL) && i<10)
   {
      if(buff[0]=='m')
      {
       i++;  
      strcpy(str, buff) ;
      mq_status = mq_send(mq,str,100,0);
      if(mq_status == 0)
      {
        printf("Sending to Message Queue done \n");
        printf("%s",str);
      }
      else
      {
          perror("Error");
          return 0;
      }
      
      }
      
   }
   mq_close(mq);
   fclose(fd);
   return 0;
}

/*#include <stdio.h>        
#include <fcntl.h>       
#include <sys/stat.h>    
#include <mqueue.h>
#include <string.h>

mqd_t cdacmq1;
struct mq_attr cdacmq1_attr;



int main(int argc,char const *argv[])
{   
    cdacmq1_attr.mq_flags=0;       // Flags (ignored for mq_open()) 
    cdacmq1_attr.mq_maxmsg=10;      // Max. # of messages on queue 
    cdacmq1_attr.mq_msgsize=100;     // Max. message size (bytes) 
    cdacmq1_attr.mq_curmsgs=0; 

    cdacmq1=mq_open("/cdacmq5", O_WRONLY | O_CREAT,S_IRUSR | S_IWUSR,&cdacmq1_attr);
    if(cdacmq1==1)
    {
        perror("Error");
        return 0 ;
    }
    else
    {
        printf("Message Queue opened successfully!");
    }
    char buff[100];
    FILE *fp;
    fp=fopen("dictionary.txt","r");
    if(fp==NULL)
    {
        printf("ERROR IN READING\n");
    }
    else
    {
        printf("File Opened Successfully!");
    }
    char str[100];
    int i=0;
    while((fgets(str,100,fp)!=NULL) && i<10)
    {
        if((str[0])=='m')
        {
            strcpy(buff,str);
            if (mq_send(cdacmq1,buff,100,0) != -1)
            {
              printf("Sending the buffer\n");
              printf("%s",buff);
            }
            else
            {
                perror("Error:");
            }
            i++;
        }
    }
    mq_close(cdacmq1);
    
    fclose(fp);
    return 0;
}*/


