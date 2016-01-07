#include<stdio.h>
#include<stdlib.h>
int main()
{
    int p,r,i,j,c,p_count,safe;
    printf("Number of Processes\n");
    scanf("%d",&p);
    p_count=p;
    printf("Number of Resources\n");
    scanf("%d",&r);
    int need[p][r],arr[p],max_res[r],max_claim[p][r],curr_alloc[p][r],dummy[r],sum,alloc[r];
    printf("Enter maximum resource vector\n");
    for(i=0;i<r;i++)
    {
        scanf("%d",&max_res[i]);
    } 
    printf("Enter current allocation table\n");
    for(i=0;i<p;i++)
    {  arr[i]=1;
        for(j=0;j<r;j++)
        {
            scanf("%d",&curr_alloc[i][j]);
        }
    }
    printf("Enter maximum resource claim table\n");
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            scanf("%d",&max_claim[i][j]);
        }
    }
    for(i=0;i<p;i++)
    {
        for(j=0;j<r;j++)
        {
            need[i][j]=max_claim[i][j]-curr_alloc[i][j];
        }
    }
    //Calculation of dummy
    for(i=0;i<r;i++)
    {   sum=0;
        for(j=0;j<p;j++)
        {
            sum+=curr_alloc[j][i];
        }
        dummy[i]=sum;
    }
    for(j=0;j<r;j++)
        {
            alloc[j]=max_res[j]-dummy[j];
        }
    //While logic
    while(p_count!=0)
    {
    safe=0;
    for(i=0;i<p;i++)
    {
        c=0;
        if(arr[i]==1)
        {
            for(j=0;j<r;j++)
            {
                if(need[i][j]-alloc[j]>0)
                {
                    c=1;
                    break;  
                }
            }
         if(c==0)
         {
             p_count--;
             arr[i]=0;
             safe=1;
             printf("P%d",i+1);
             for(j=0;j<r;j++)
             {
                 alloc[j]+=need[i][j];
             }
         }
         
        }//If condition
    }
    if(safe==0)
    {
        printf("\nThe system is in an unsafe state");
        break;   
    }
    }
    if(safe)
    {
        printf("\nThe system is in a safe state");
    }
    return 1;    
}
