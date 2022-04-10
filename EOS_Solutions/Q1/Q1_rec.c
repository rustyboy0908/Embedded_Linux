#include <stdio.h>        
#include <fcntl.h>       
#include <sys/stat.h>    
#include <mqueue.h>
#include <string.h>

mqd_t mq;
unsigned char buff[100];
int i =0;
struct mq_attr rishabh_attr ;
int main()
{

   rishabh_attr.mq_flags=0;
   rishabh_attr.mq_maxmsg=10;
   rishabh_attr.mq_msgsize=100;
   rishabh_attr.mq_curmsgs=0;

   
   //mq= mq_open("/rishabh",O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &rishabh_attr);
   mq = mq_open("/JMD8",O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &rishabh_attr);
   if(mq == -1)
   {
     perror("ERROR");
     return 0;
   }
   else
   {
     printf("Successfully opened MQ!");
   }

   while(i<10)
   {
    mq_receive(mq,buff,100,0);
    printf("Message rec\n");
    printf("%s",buff);
    i++;
   }
   mq_unlink("/JMD8"); //Message queue will get cleared.
   mq_close(mq);
   return 0;
}

/*#include <stdio.h>        
#include <fcntl.h>       
#include <sys/stat.h>    
#include <mqueue.h>
#include <string.h>

mqd_t cdacmq1;
struct mq_attr cdacmq1_attr;
unsigned char buff[100];
int msg_prio;
int c;


int main(int argc,char const *argv[])
{   
    cdacmq1_attr.mq_flags=0;       // Flags (ignored for mq_open()) 
    cdacmq1_attr.mq_maxmsg=10;      // Max. # of messages on queue 
    cdacmq1_attr.mq_msgsize=100;     // Max. message size (bytes) 
    cdacmq1_attr.mq_curmsgs=0; 

    cdacmq1=mq_open("/cdacmq5", O_RDONLY,S_IRUSR | S_IWUSR,&cdacmq1_attr);
    int i=0;
    while(i<10)
    {   
        mq_receive(cdacmq1,buff,100,&msg_prio);
        
        printf("RECEIVED MESSAGE :%s\n %d\n",buff,msg_prio);
        c=strlen(buff);
        printf("LENGTH:%d\n",c);
        i++;
    }
    mq_close(cdacmq1);
    return 0;
}*/

