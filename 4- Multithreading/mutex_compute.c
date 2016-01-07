#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t lock;
double maximum=0;
double minimum=0;
double total=0;
double average=0;
int k=0;
int count=0;
int flag=0;
void *Add1(void *dummy)
{  //priintf("Inside Add Function\n");  
  
    while(1)
    {  // printf("inside while loop\n");
        double num=0;
        if(k==1)
        {
            pthread_exit(NULL);
            return NULL;
        }
        pthread_mutex_lock(&lock);
        if (scanf("%lf",&num)==EOF)
        {
          //  printf("Inside EOF CONDITION\n");
            k=1;
           // printf("VALUE OF K %d\n",k);
            pthread_mutex_unlock(&lock);
            
            return NULL;
        }
        else
        {    //printf("In Mutex Lock %lf\n",num);
          

            if(flag==0)
            {
                 flag=1;
                 maximum=num;
                 minimum=num;
                 total+=num;
                 count++;
                 average=(total/count);
            }
            else
            {
                if(num>maximum)
                {
                    maximum=num;
                }
               else if(num<minimum)
               {
                   minimum=num;
               }
               total+=num;
               count++;
               average=(total/count);
               //printf("%lf %lf %lf\n",maximum,minimum,total);
            }
        }
        pthread_mutex_unlock(&lock);

        
    }
    
    return NULL;
}

int main(int argc,char *argv[])
{
    //printf("IN First line\n");
    pthread_t t[3];
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    int i=0;
    for(i;i<=2;i++)
    {
        if(pthread_create(&t[i],NULL,Add1,(void *)t[i]))
        {
            printf("Error message creating thread\n");
            return 1;
        }
    } 
    while(1)
    {  // printf("inside while loop\n");
        double num=0;
        if(k==1)
        {
            pthread_exit(NULL);
            break;
        }
        pthread_mutex_lock(&lock);
        if (scanf("%lf",&num)==EOF)
        {
          //  printf("Inside EOF CONDITION\n");
            k=1;
           // printf("VALUE OF K %d\n",k);
            pthread_mutex_unlock(&lock);
            
            break;
        }
        else
        {    //printf("In Mutex Lock %lf\n",num);
          

            if(flag==0)
            {
                 flag=1;
                 maximum=num;
                 minimum=num;
                 total+=num;
                 count++;
                 average=(total/count);
            }
            else
            {
                if(num>maximum)
                {
                    maximum=num;
                }
               else if(num<minimum)
               {
                   minimum=num;
               }
               total+=num;
               count++;
               average=(total/count);
               //printf("%lf %lf %lf\n",maximum,minimum,total);
            }
        }
        pthread_mutex_unlock(&lock);

        
    }
 

   int z=0;
   for (z;z<=2;z++)
   {
       pthread_join(t[z],NULL);
   }
   pthread_mutex_destroy(&lock);
   //printf("%lf %lf %lf %lf",maximum,minimum,total,average);
   printf("max: %.0f\n",maximum);
   printf("min: %.0f\n",minimum);
   printf("average: %.2f",average);
    return 0;
}

