/*Server*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 15000
#define BUF_SIZE 1024
int main() {
    int cont, create_socket, new_socket, fd;
    socklen_t addrlen;
    char buffer[BUF_SIZE];
    char fname[256];
    struct sockaddr_in address;
    // Create socket
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("The socket was created\n");
    // Zero out the address struct
    memset(&address, 0, sizeof(address));
    // Define server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    // Bind socket to address
    if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        close(create_socket);
        exit(1);
    }
    printf("Binding Socket\n");
    // Listen for incoming connections
    if (listen(create_socket, 3) < 0) {
        perror("Listen failed");
        close(create_socket);
        exit(1);
    }
    printf("Waiting for a client connection...\n");
        addrlen = sizeof(address);
    new_socket = accept(create_socket, (struct sockaddr *)&address, &addrlen);
        if (new_socket < 0) {
        perror("Accept failed");
        close(create_socket);
        exit(1);
    }
    printf("The Client %s is Connected...\n", inet_ntoa(address.sin_addr));
    // Receive filename request from client
    memset(fname, 0, sizeof(fname));
    recv(new_socket, fname, sizeof(fname) - 1, 0);
    printf("A request for filename %s Received..\n", fname);
    // Open file
    if ((fd = open(fname, O_RDONLY)) < 0) {
        perror("File Open Failed");
        close(new_socket);
        close(create_socket);
        exit(1);
    }
    // Send file content
    while ((cont = read(fd, buffer, BUF_SIZE)) > 0) {
        send(new_socket, buffer, cont, 0);
    }
        printf("Request Completed\n");
    // Close sockets
    close(fd);
    close(new_socket);
    close(create_socket);
        return 0;
}



