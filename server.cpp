#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() 
{
    // create ipv4, tcp, default socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Server created socket\n");

    // create address information
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    // bind socket
    bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr));
    printf("Server bound socket\n");

    // listen for connections (max 3)
    listen(socket_fd, 3);
    printf("Server listening on port 8080\n");

    // accept limited number of connections
    for (int number=0; number<3; number++)
    {
        // create client address
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // accept a connection
        int client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_len);

        // read message
        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer));
        printf("Received: \n%s\n", buffer);

        // create response
        const char *response = "Hello from server!\n";
        send(client_fd, response, strlen(response), 0);
        printf("Server sent response\n");

        // close client socket 
        close(client_fd); 
        printf("Server closed client socket\n");
    }

    // close server socket
    close(socket_fd);
    printf("Server closed socket\n");

    return 0;
}