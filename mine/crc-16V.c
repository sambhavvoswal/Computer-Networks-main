#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// XOR operation between two binary strings
void xor1(char *result, const char *a, const char *b) {
    int n = strlen(b);
    for (int i = 1; i < n; i++) {
        result[i - 1] = (a[i] == b[i]) ? '0' : '1';
    }
    result[n - 1] = '\0';
}

// Modulo-2 Division Function
void mod2div(char *remainder, const char *dividend, const char *divisor) {
    int pick = strlen(divisor);
    int n = strlen(dividend);

    char *tmp = (char *)malloc(n + 1);  
    strncpy(tmp, dividend, pick);
    tmp[pick] = '\0';

    while (pick < n) {
        char res[100];

        if (tmp[0] == '1') {
            xor1(res, divisor, tmp);
        } else {
            char zeroDivisor[100];
            memset(zeroDivisor, '0', pick);
            zeroDivisor[pick] = '\0';
            xor1(res, zeroDivisor, tmp);
        }

        tmp[0] = '\0';
        strcat(tmp, res);
        strncat(tmp, &dividend[pick], 1);

        pick++;
    }

    char finalRes[100];
    if (tmp[0] == '1') {
        xor1(finalRes, divisor, tmp);
    } else {
        char zeroDivisor[100];
        memset(zeroDivisor, '0', pick);
        zeroDivisor[pick] = '\0';
        xor1(finalRes, zeroDivisor, tmp);
    }

    strcpy(remainder, finalRes);
    free(tmp);
}

// Encoding the Data
void encodeData(const char *data, const char *key, char *codeword) {
    int l_key = strlen(key);
    int dataLen = strlen(data);

    // Append n-1 zeros to the data
    char *appended_data = (char *)malloc(dataLen + l_key);
    strcpy(appended_data, data);
    memset(appended_data + dataLen, '0', l_key - 1);
    appended_data[dataLen + l_key - 1] = '\0';

    char remainder[100];
    mod2div(remainder, appended_data, key);

    // Create the codeword: data + remainder
    strcpy(codeword, data);
    strcat(codeword, remainder);

    printf("Remainder: %s\n", remainder);
    printf("Encoded Data (Data + Remainder): %s\n", codeword);

    free(appended_data);
}

// Receiver Side: Checking for Errors
void receiver(const char *data, const char *key) {
    char currXor[100];
    mod2div(currXor, data, key);

    if (strchr(currXor, '1') != NULL) {
        printf("\nThere is some error in data.\n");
    } else {
        printf("\nCorrect message received.\n");
    }
}

int main() {
    char data[100], key[100], received[100];

    // User Input for Data and Key
    printf("Enter the binary data: ");
    scanf("%s", data);

    printf("Enter the binary key (divisor): ");
    scanf("%s", key);

    // Encoding
    printf("\nSender side...\n");

    char codeword[200];  // Holds the encoded data (data + remainder)
    encodeData(data, key, codeword);

    // Receiver side
    printf("\nReceiver side...\n");
    printf("Enter the received message: ");
    scanf("%s", received);

    receiver(received, key);

    return 0;
}
