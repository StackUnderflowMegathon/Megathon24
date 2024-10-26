//#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
//#include<fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include<stdlib.h>
#define CONNECTION_PORT 3500

int connect_to_server(char* ip){
    struct sockaddr_in server_address;
    int socket_descriptor = socket(AF_INET,SOCK_STREAM,0);
    if(socket_descriptor<0)
   {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
   }  
    int status=0;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(CONNECTION_PORT);
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    //server_address.sin_addr.s_addr =INADDR_ANY;
    server_address.sin_zero[8]='\0';
    status=connect(socket_descriptor,(struct sockaddr*)&server_address, sizeof(server_address));
    if(status<0)
   {
        perror("Couldn't connect with the server");
        exit(EXIT_FAILURE);
   }

   return socket_descriptor;
}

int main()
{
    
    char* message="Hi";
    char recieve_buffer[100];
    
    int socket_descriptor = connect_to_server("");


    write(socket_descriptor, message, strlen(message));

    int s = 0;
    while(s == 0){
          s = read(socket_descriptor, recieve_buffer, 100);
          printf("Message from server: %s\n", recieve_buffer);
    }
    close(socket_descriptor);
    return 0;
}
