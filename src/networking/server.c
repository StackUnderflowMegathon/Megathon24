#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include "../constants.h"

#define PORT 3500
#define MAX_CLIENTS 4
#define BUFFER_SIZE 1024

int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *client_socket) {
    int sock = *((int *)client_socket);
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';

        // Broadcast message to other clients
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < client_count; i++) {
            if (clients[i] != sock) {
                send(clients[i], buffer, strlen(buffer), 0);
            }
        }
        pthread_mutex_unlock(&mutex);
    }

    // Remove client on disconnect
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] == sock) {
            clients[i] = clients[--client_count];
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    close(sock);
    return NULL;
}

int main() {
    int server_socket, client_socket, temp = 1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t tid;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,&temp ,sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr);

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        pthread_mutex_lock(&mutex);
        if (client_count < MAX_CLIENTS) {
            clients[client_count++] = client_socket;
            pthread_create(&tid, NULL, handle_client, &client_socket);
            printf("New client connected\n");
            for (int i = 0; i < client_count; i++) {
                char buffer[8];
                sprintf(buffer, "%d%c%d", client_count-1, 'M', 5);
                printf("sending %s\n", buffer);
                write(clients[i], buffer, strlen(buffer));            
            }
        } else {
            printf("Max clients connected. Connection refused.\n");
            close(client_socket);
        }
        pthread_mutex_unlock(&mutex);
    }

    return 0;
}
