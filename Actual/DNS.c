#include <stdio.h>
#include <netdb.h>        // for gethostbyname()
#include <arpa/inet.h>    // for inet_ntoa()
#include <string.h>       // for memcpy()

// Usage: ./a.out <hostname>

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        return 1;
    }

    // Get host information using hostname
    struct hostent *host = gethostbyname(argv[1]);

    // If resolution fails
    if (!host) {
        printf("Could not resolve hostname.\n");
        return 1;
    }

    // Print the official name of the host
    printf("Official name: %s\n", host->h_name);

    // Loop through all IP addresses (can be multiple)
    for (int i = 0; host->h_addr_list[i]; i++) {
        struct in_addr addr;

        // Copy the IP address from the hostent structure
        memcpy(&addr, host->h_addr_list[i], sizeof(struct in_addr));

        // Convert the IP address to string and print it
        printf("IP Address: %s\n", inet_ntoa(addr));
    }

    return 0;
}
