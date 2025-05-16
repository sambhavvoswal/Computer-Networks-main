#include <stdio.h>
int main(){
    int data[5];    // 1-based indexing: data[1] to data[4]
    int cw[8];      // 1-based indexing: cw[1] to cw[7]
    int rev[8];     // 1-based indexing
    int i, c, c1, c2, c3;

    printf("Enter 4-bit dataword:\n");
    for(i = 1; i <= 4; i++)
        scanf("%d", &data[i]);

    // Assign data bits to codeword positions (3, 5, 6, 7)
    cw[3] = data[1];
    cw[5] = data[2];
    cw[6] = data[3];
    cw[7] = data[4];

    // Calculate parity bits (positions 1, 2, 4)
    cw[1] = cw[3] ^ cw[5] ^ cw[7];
    cw[2] = cw[3] ^ cw[6] ^ cw[7];
    cw[4] = cw[5] ^ cw[6] ^ cw[7];

    printf("\nGenerated codeword:\n");
    for(i = 1; i <= 7; i++)
        printf("%d", cw[i]);
    printf("\n");

    printf("Enter the received codeword:\n");
    for(i = 1; i <= 7; i++)
        scanf("%d", &rev[i]);

    // Syndrome calculation
    c1 = rev[1] ^ rev[3] ^ rev[5] ^ rev[7];
    c2 = rev[2] ^ rev[3] ^ rev[6] ^ rev[7];
    c3 = rev[4] ^ rev[5] ^ rev[6] ^ rev[7];

    c = c1 * 1 + c2 * 2 + c3 * 4;

    if(c == 0)
        printf("\nNo error detected in transmission.\n");
    else {
        printf("\nError found at position: %d\n", c);
        printf("Original data sent by sender:\n");
        for(i = 1; i <= 7; i++)
            printf("%d", cw[i]);

        printf("\nReceived data:\n");
        for(i = 1; i <= 7; i++)
            printf("%d", rev[i]);

        // Correct the error
        rev[c] = !rev[c];

        printf("\nCorrected codeword:\n");
        for(i = 1; i <= 7; i++)
            printf("%d", rev[i]);
        printf("\n");
    }
    return 0;
}
