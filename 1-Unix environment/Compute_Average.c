
 /*=================================================================
 Name        : Hello.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#include<stdbool.h>

int main(int argc,char *argv[])
{
setbuf(stdout,NULL);
if (argc < 2)
    {
        printf("Error: no input file specified\nUsage: average numbers.dat\n");
        exit(1);
    }
char * filename="numbers.dat";
//if(filename!=argv[1])
  //  {
    //    printf("File name doesnot match");
      //  exit(2);
   // }
FILE *fp=fopen("numbers.dat","r+");
if(fp==NULL)
{
    printf("Failed to open file!\n");
    exit(3);
}
float a=0;
float sum;
int count=0;
while(fscanf(fp,"%f",&a)!= EOF)
    {
	    count++;
	    sum+=a;
    }
printf("The average of the 10 numbers in file “numbers.dat” is:\n");
printf("%.1f",sum/count);
//printf("\n%d",count);
return 0;
}



