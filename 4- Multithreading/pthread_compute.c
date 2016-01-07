#include<sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *Add1(void *numbers1)
{
    
    int i=0;
    double *sum=(double *)numbers1;
    int add=0;
    int max=sum[0];
    int min=sum[0];
    for(i;i<50;i++)
    {
        add+=sum[i];
        if(sum[i]>max)
        {
            max=sum[i];
        }
        else if (sum[i]<min && sum[i]!=0)
        {
            min=sum[i];
        }
    }
    sum[0]=max;
    sum[1]=min;
    sum[2]=add;
    
    return NULL;
}

void *Add2(void *numbers1)
{

    int i=0;
    double *sum=(double *)numbers1;
    int add=0;
    int max=sum[0];
    int min=sum[0];
    for(i;i<50;i++)
    {
        add+=sum[i];
        if(sum[i]>max)
        {
            max=sum[i];
        }
        else if (sum[i]<min && sum[i]!=0)
        {
            min=sum[i];
        }
    }

    sum[0]=max;
    sum[1]=min;
    sum[2]=add;
  
    return NULL;
}
void *Add3(void *numbers1)
{

    int i=0;
    double *sum=(double *)numbers1;
    int add=0;
    int max=sum[0];
    int min=sum[0];
    for(i;i<50;i++)
    {
        add+=sum[i];
        if(sum[i]>max)
        {
            max=sum[i];
        }
        else if (sum[i]<min && sum[i]!=0)
        {
            min=sum[i];
        }
    }
 
    sum[0]=max;
    sum[1]=min;
    sum[2]=add;

    return NULL;
}

int main(int argc,char *argv[])
{
    double numbers[100]={0};
    int i=0,j=0,sum=0;
    int k=0;
    while(scanf("%lf",&numbers[i])!=EOF)
    {
        i++;
    }
    /*for (j;j<i;j++)
    {
        printf("%lf\n",numbers[j]);
    }
    */
   pthread_t t1,t2,t3;
   double a[50]={0};
   double b[50]={0};
   double c[50]={0};
   double d[50]={0};
   int d_i=0;
   int d_sum=0;
   int div=i/4;
   int m=0;
   int cp=0;
   for(m;m<div;m++)
   {
       a[m]=numbers[m];
       
   }
   for(m;m<(2*div);m++)
   {   
       b[cp++]=numbers[m];
       

   }
   cp=0;
   for(m;m<(3*div);m++)
   {
       c[cp++]=numbers[m];
      

   }
   cp=0;
   for(m;m<i;m++)
   {
       d[cp++]=numbers[m];
   }
   int d_max=d[0];
   int d_min=d[0];
   for(d_i;d_i<50;d_i++)
    {   d_sum+=d[d_i];
        if(d_max<d[d_i])
        {
            d_max=d[d_i];
        }
        else if(d_min>d[d_i] && d[d_i]!=0)
        {
            d_min=d[d_i];
        }
    }
   d[0]=d_max;
   d[1]=d_min;
   d[2]=d_sum;

   //printf("%lf %lf %lf\n",a[0],a[1],a[2]);
   //printf("%lf %lf %lf\n",b[0],b[1],b[2]);
   //printf("%lf %lf %lf\n",c[0],c[1],c[2]);
   //printf("%lf %lf %lf\n",d[0],d[1],d[2]);
   
   if(pthread_create(&t1,NULL,Add1,&a))
    {
        printf("Error message creating thread\n");
        return 1;
    }
   if(pthread_create(&t2,NULL,Add2,&b))
    {
        printf("Error message creating thread\n");
        return 1;
    }
   if(pthread_create(&t3,NULL,Add3,&c))
    {
        printf("Error message creating thread\n");
        return 1;
    }
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    /*
    for (k;k<i;k++)
    {
        printf("%lf\n",numbers[k]);
    }

    pthread_exit(NULL);
*/

    //printf("%lf %lf %lf",b[0],b[1],b[2]);
    float maximum=a[0];
    float minimum=a[1];
    double summation=0;
    double ans;
    if (b[0]>maximum)
        {
            maximum=b[0];
        }
    
    if (c[0]>maximum)
        {
            maximum=c[0];
        }

    if (d[0]>maximum)
        {
            maximum=d[0];
        }
    if (b[1]<minimum)
        {
            minimum=b[1];
        }
    if (c[1]<minimum)
        {
            minimum=c[1];
        }
    if (d[1]<minimum)
        {
            minimum=d[1];
        }
    summation=a[2]+b[2]+c[2]+d[2];
    ans=(summation/i);
    printf("max: %.0f\n",maximum);
    printf("min: %.0f\n",minimum);
    printf("average: %.2f",ans); 
    return 0;
}
