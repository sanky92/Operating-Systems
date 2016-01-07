#include<sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
    int pid,c_pid,i,status;
    char command[1024];
    char command_1[1024];

    int count=0;
    char *token;
    char **tokens=malloc(64*sizeof(char*));
    
 
    while(1)
    {
        printf("$ ");
        i=getchar();
        int position=0;
        if(i==EOF)
        {
            exit(0);
        }
        while(1)
        {
            if(i=='\n')
            {
	       command[position]='\0';
               break;
            }
            command[position++]=i;
            i=getchar();
            if(i==EOF)
            {
                exit(1);
            }
        }
    
    
   

    int position_1=0;
    token=strtok(command," ");
    while(token!=NULL)
    {
        
    
       tokens[position_1++]=token;
        token=strtok(NULL," ");
    }
    tokens[position_1]=token;

//Fork and Execvp Logic
    
   c_pid=fork();
   if(c_pid==0)
    {
        execvp(tokens[0],tokens);
        printf("EXEC Failed\n");
  
    }
    else 
    {
        while(wait(&status)!=c_pid);
    }

}//While
}//main

