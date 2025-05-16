//Parity Bit Generator
#include<stdio.h>

int main()
{
	int n,bin=0,place=1,count=0;
	printf("Enter the decimal number:\n");
		scanf("%d",&n);
	
	int temp=n;
	
	while(n>0)
	{
		int digit=n%2;
		bin+=(digit*place);
		n/=2;
		place=place*10;
	}
	
	printf("Binary number : %d\n",bin);
	
	while(temp>0)
	{
		if(temp&1)
			count++;
		temp=temp>>1;	
	}
	
	printf("Number of ones: %d",count);
	
	int ch,output;
	int recived;
	
	printf("Enter the choice:\n");
	printf("1-Even Parity\n2-Odd Parity\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1: if(count%2==0)
				{
					output = bin*10+0;
					printf("Parity bit generated is 0\n");
					printf("Output: %d",output);
				}
				else
				{
					output=bin*10+1;
					printf("\nParity bit generated is 1\n");
					printf("Output: %d",output);
				}
				
				printf("\nEnter the reciver data:\n");
				scanf("%d",&recived);
				
				if(recived==bin)
					printf("No error in Data\n");
				else
					printf("Error in Data\n");
					
				return 0;
		
		case 2: if(count%2!=0)
				{
					output = bin*10+1;
					printf("Parity bit generated is 1\n");
					printf("Output: %d",output);
				}
				else
				{
					output=bin*10+0;
					printf("\nParity bit generated is 0\n");
					printf("Output: %d",output);
				}
				
				printf("\nEnter the reciver data:\n");
				scanf("%d",&recived);
				
				if(recived==bin)
					printf("No error in Data\n");
				else
					printf("Error in Data\n");
					
				return 0;
				
		default: printf("Invalid Choice\n");
				break;
	}
	return 0;
	
}
	