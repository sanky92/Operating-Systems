#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int arg, char *argv[])
{

	setbuf(stdout, NULL);
	float min;
	float max;
	float average;
	int count=0;
	float number;
	float sum=0;
	while(scanf("%f",&number)!=EOF)//possible
	{
		if (count==0)
		    {   min=number;
		        max=number;
		        count++;
		        sum+=number;
		    }
		else
		    {
			    if(number<min)
			    	min=number;
			    else if(number>max)
			    	max=number;
			    count++;
			    sum+=number;

		    }

	}
	printf("max: %.0f\n",max);
	printf("min: %.0f\n",min);
	printf("average: %.2f\n",(sum/count));

	return 0;
}

