#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
int count1=0,count2=0,count3=0,count4=0;
void Thread1(int k)
{
    
    while (count1<k)
        {
            printf("B");
            fflush(stdout);
            count1++;
        }
}
void Thread2(int k)
{
    
    while(count2<k)
        {
            printf("C");
            fflush(stdout);
            count2++;
        }
}
void Thread3(int k)
{

    while (count4<k)
        {
            printf("D");
            fflush(stdout);
            count4++;
        }
}

void Thread0(int k)
{

    while(count3<k)
        {
            printf("A");
            fflush(stdout); 
            count3++;
        }
    exit(2);
}

int main(int argc, char* argv[])
{
    
    int pid1,pid2,wpid,pid3;
    int status1,status2,status3;
    
   
    int k,i;
    k=atoi(argv[1]);
    
    if (k<=0||k>=10000000)
    {
        k=10;
    }
    pid1=fork();
    if (pid1==0)
    {
        Thread1(k);
        exit(1);   
    }
    pid2=fork();
    if(pid2==0)
    {
        Thread2(k);
        exit(0);
    }
    pid3=fork();
    if(pid3==0)
    {
        Thread3(k);
        exit(3);
    }

    Thread0(k);
    while(wait(&status1)!=pid1);
    while(wait(&status2)!=pid2);
    while(wait(&status3)!=pid3); 
    return 0;
    
}
