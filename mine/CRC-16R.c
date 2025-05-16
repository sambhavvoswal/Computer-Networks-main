//CRC-16
#include<stdio.h>
#include<stdlib.h>
#define div 17

void binarydiv(int dataword[], int n, int k, int divisor[]) 
{
    int rem[n];
    int i,j;
    
    for (i = 0; i < n; i++) 
        rem[i] = dataword[i];
    
    for (i = 0; i <= n - div; i++) 
        if (rem[i] == 1) 
            for (j = 0; j < div; j++) 
                rem[i + j] ^= divisor[j];
                
    for (i = 0; i < div - 1; i++) 
        dataword[k + i] = rem[n - div + 1 + i];
}

void printDataword(int dataword[],int k,int n)
{
	int i;
	for (i = k; i < n; i++) 
        	printf("%d", dataword[i]);
}

void detect(int user[],int k,int n)
{
	int error=0;
	int i;
	for (i = k; i < n; i++) 
	{
        if (user[i] != 0) 
	{
            error = 1;
            break;
        }
    }
    
	if (error == 0)
        printf("no errors");
    else 
        printf("error detected");
    
}

int main() 
{
    int dataword[25];
    int divisor[div] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    int n = 24, k = 8;
    int dtwd[25];
    int i;

    printf("Enter data word of 8 bits:\n");
    for (i = 0; i < k; i++) 
        scanf("%d", &dataword[i]);
    
    for (i = 0; i < k; i++) 
        dtwd[i] = dataword[i];
    
    printf("Entered data word is:\n");
    printDataword(dataword,0,k);

    for (i = k; i < n; i++) 
        dataword[i] = 0;
    

    printf("\n0's appended data word is:\n");
    printDataword(dataword,0,n);

    binarydiv(dataword, n, k, divisor);

    printf("\nDataword after binary division:\n");
    printDataword(dataword,0,n);

    printf("\nRemainder:\n");
    printDataword(dataword,k,n);
    printf("\n");

    printf("append the remender to 8 bit dataword :\n");
    for (i = k; i < n; i++) 
        dtwd[i] = dataword[i];
        
    printDataword(dtwd,0,n);

    printf("\n");

    binarydiv(dtwd, n, k, divisor);
  
    printf("\nRemainder at receiver side:\n");
        printDataword(dtwd,k,n);

    printf("\n");

    detect(dtwd,k,n);
    printf("\n");
    printf("enter 24 bit recived data\n");
    int user[24];
    
    for (i=0;i<n;i++)
		scanf("%d",&user[i]);
		
	binarydiv(user, n, k, divisor);
	
    detect(user,k,n);
    
    return 0;
}
//1 0 1 1 0 0 1 1 1 0 0 1 0 1 1 1 1 0 1 1 1 0 0 0
