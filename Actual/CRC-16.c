#include <stdio.h>
#include <stdlib.h>

#define div 17  // Length of CRC-16 polynomial (degree + 1)

// ---------- Binary Division Function (Mod-2 Division) ----------
void binarydiv(int dataword[], int n, int k, int divisor[]) 
{
    int rem[n];  // Remainder
    int i, j;

    // Copy dataword into remainder array
    for (i = 0; i < n; i++) 
        rem[i] = dataword[i];

    // Perform modulo-2 division
    for (i = 0; i <= n - div; i++) 
        if (rem[i] == 1)  // Only divide if current bit is 1
            for (j = 0; j < div; j++) 
                rem[i + j] ^= divisor[j];  // XOR with divisor

    // Store the remainder in the last bits of dataword
    for (i = 0; i < div - 1; i++) 
        dataword[k + i] = rem[n - div + 1 + i];
}

// ---------- Helper Function to Print Dataword ----------
void printDataword(int dataword[], int start, int end)
{
    int i;
    for (i = start; i < end; i++) 
        printf("%d", dataword[i]);
}

// ---------- Error Detection Function ----------
void detect(int user[], int k, int n)
{
    int error = 0;
    int i;

    // Check if remainder bits are all zero
    for (i = k; i < n; i++) 
    {
        if (user[i] != 0) 
        {
            error = 1;
            break;
        }
    }

    if (error == 0)
        printf("No errors\n");
    else 
        printf("Error detected\n");
}

// ---------- Main Function ----------
int main() 
{
    int dataword[25];  // Holds original + remainder
    int dtwd[25];      // For transmission (copy of dataword)
    int i;

    // CRC-16 Polynomial: x^16 + x^12 + x^5 + 1 => 10001000000100001
    int divisor[div] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    int k = 8;         // Length of original dataword
    int n = 24;        // Total length = dataword + 16 zeros (div - 1)

    printf("Enter data word of 8 bits:\n");
    for (i = 0; i < k; i++) 
        scanf("%d", &dataword[i]);

    // Store a copy of original dataword
    for (i = 0; i < k; i++) 
        dtwd[i] = dataword[i];

    printf("Entered data word is:\n");
    printDataword(dataword, 0, k);

    // Append 16 zeros to dataword for CRC calculation
    for (i = k; i < n; i++) 
        dataword[i] = 0;

    printf("\n0's appended data word is:\n");
    printDataword(dataword, 0, n);

    // Perform binary division to get CRC bits
    binarydiv(dataword, n, k, divisor);

    printf("\nDataword after binary division:\n");
    printDataword(dataword, 0, n);

    printf("\nRemainder (CRC bits):\n");
    printDataword(dataword, k, n);
    printf("\n");

    // Append CRC to original dataword to get transmitted code
    printf("Final codeword (data + CRC):\n");
    for (i = k; i < n; i++) 
        dtwd[i] = dataword[i];

    printDataword(dtwd, 0, n);
    printf("\n");

    // Simulate receiver side check
    binarydiv(dtwd, n, k, divisor);

    printf("\nRemainder at receiver side:\n");
    printDataword(dtwd, k, n);
    printf("\n");

    detect(dtwd, k, n);  // Should show no error

    // ---------- Now simulate user-entered received code ----------
    printf("Enter 24-bit received data (possibly with error):\n");
    int user[24];
    for (i = 0; i < n; i++)
        scanf("%d", &user[i]);

    // Check for errors in received data
    binarydiv(user, n, k, divisor);
    detect(user, k, n);

    return 0;
}

//1 0 1 1 0 0 1 1 1 0 0 1 0 1 1 1 1 0 1 1 1 0 0 0
