#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include<stdlib.h>
#define CONNECTION_PORT 3500

int main()
{
    int socket_descriptor;
    int client_socket;
    char storage_buffer[80];
    int length_of_address;
    int option_value=1;
    struct sockaddr_in server_address;
    struct sockaddr_in connection_address;
    //char* message = "Pranshuuuuuul";
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_descriptor<0)
   {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
   }     
    int status=setsockopt(socket_descriptor, SOL_SOCKET,SO_REUSEADDR , &option_value,sizeof(option_value));
    if(status<0){
        perror("Couldn't set options");
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(CONNECTION_PORT);
    inet_pton(AF_INET, "0.0.0.0", &server_address.sin_addr);
    server_address.sin_zero[8]='\0';
    status=bind(socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    if(status<0){
        perror("Couldn't bind socket");
        exit(EXIT_FAILURE);
    }
    status=listen(socket_descriptor,4);
    if(status<0){
        perror("Couldn't listen for connections");
        exit(EXIT_FAILURE);
    }
    length_of_address = sizeof(connection_address);
    client_socket = accept(socket_descriptor, (struct sockaddr*)&connection_address, &length_of_address);
    if(client_socket<0){
        perror("Couldn't establish connection with client");
        exit(EXIT_FAILURE);
    }
    read(client_socket, storage_buffer, 80);
    storage_buffer[79] = '\0';
    printf("Message from client: %s \n",storage_buffer);


    while(1){
        char message[100];
        scanf("%s", message);
        send(client_socket, message, strlen(message)+1, 0);
    }
    close(socket_descriptor);
    close(client_socket);
    return 0;
}
