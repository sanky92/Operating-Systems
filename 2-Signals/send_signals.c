#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
int count=0;
void sig_handler(int signum)
{ if(signum==SIGUSR1)
    {
        count++;
    
    }
  else if(signum==SIGUSR2)
{
    
}
  else
    { printf("Signals: %d\n",count);
      exit (1);
    }
}
int main(int argc, char *argv[])
{
    setbuf(stdout,NULL);
   if( signal(SIGUSR1,sig_handler)==SIG_ERR)
    {
        printf("Unable to create handler for sigusr1");
    }
    if (signal(SIGUSR2,sig_handler)==SIG_ERR)
    {
        printf("Unable to create handler for sigusr2");    
    }
    signal(SIGINT,sig_handler);
    int pid=getpid();
    //printf("%d",pid);
    
    while(1);
    sleep(1);
    return 0;
}

