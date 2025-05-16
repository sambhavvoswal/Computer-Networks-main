/*Client*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORT 15000
#define BUF_SIZE 1024
int main(int argc, char *argv[]) {
    int create_socket, cont;
    char buffer[BUF_SIZE];
    char fname[256];
    struct sockaddr_in address;

    // Check for correct usage
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        exit(1);
    }

    // Create socket
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("The Socket was created\n");

    // Zero out the address struct
    memset(&address, 0, sizeof(address));

    // Define server address
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    
    // Convert IP address from text to binary
    if (inet_pton(AF_INET, argv[1], &address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(create_socket);
        exit(1);
    }

    // Connect to server
    if (connect(create_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Connection failed");
        close(create_socket);
        exit(1);
    }

    printf("The connection was accepted with the server %s...\n", argv[1]);
    // Get the filename from the user
    printf("Enter The Filename to Request: ");
    scanf("%255s", fname);  // Prevent buffer overflow

    // Send filename to server
    send(create_socket, fname, strlen(fname) + 1, 0);
    printf("Request Accepted... Receiving File...\n\n");
    printf("The contents of the file are...\n\n");

    // Receive and print file content
    while ((cont = recv(create_socket, buffer, BUF_SIZE, 0)) > 0) {
        write(STDOUT_FILENO, buffer, cont);
    }

    if (cont < 0) {
        perror("Receive failed");
    }

    printf("\nEOF\n");
    // Close socket
    close(create_socket);
    return 0;
}
