#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
int c=0,s=0,q=0;
void sig_handler(int signum)
{
    if(signum==SIGINT)
        {   c++;
            printf("I");
            fflush(stdout);
        }
    if(signum==SIGQUIT)
        {
            q++;
            printf("Q");
            fflush(stdout);
        }
    if(signum==SIGTSTP)
        {
            s++;
            printf("S");
            fflush(stdout);
        }
     if(s==3)
         {
             printf("\nInterrupt: %d",c);
             printf("\nStop: %d",s);
             printf("\nQuit: %d",q);
             exit(0);
         }
}



int main(int argc, char *argv[])
{
    setbuf(stdout,NULL);
    signal(SIGTSTP,sig_handler);
    signal(SIGINT,sig_handler);
    signal(SIGQUIT,sig_handler);
    

    while(1);
    sleep(1);
    return 0;
}
