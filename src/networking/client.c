// #include<sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
// #include<fcntl.h>
#include <stdio.h>
#include <pthread.h>
// #include "../constants.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define CONNECTION_PORT 3500

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds){ // cross-platform sleep function
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

void* send_packet(void*  arg){
	int SocketDescriptor = (*((struct thread_args *)arg)).SocketDescriptor;
	int pid = (*((struct thread_args *)arg)).PlayerId;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	while(1){
		pthread_mutex_lock(&mutex);
		char buffer[8];
		sprintf(buffer, "%d%c%d", pid, 'M', (*((struct thread_args *)arg)).positions[pid]);
		write(SocketDescriptor, buffer, strlen(buffer));
		pthread_mutex_unlock(&mutex);

		sleep_ms(50);
	}
}

void *receive_packets(void *arg)
{
	char buffer[50];
	int bytes_read;
	pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

	while ((bytes_read = read((*((struct thread_args *)arg)).SocketDescriptor, buffer, sizeof(buffer) - 1)) > 0)
	{
		fprintf(stderr, "%d\n", bytes_read);
		buffer[bytes_read] = '\0';
		pthread_mutex_lock(&mtx);
		(*(struct thread_args *)arg).state[buffer[0]-'0'] = buffer[1];
		fprintf(stderr, "%s\n", buffer);
		int i = 2;
		int pos= 0;
		while(buffer[i] != '\0'){
			pos = pos*10 + (buffer[i]-'0');
			i++;
		}
		pthread_mutex_unlock(&mtx);

		(*(struct thread_args *)arg).positions[buffer[0]-'0'] = pos;
	}
}

int connect_to_server(char *ip)
{
	pthread_t tid;

	struct sockaddr_in server_address;
	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_descriptor < 0)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	int status = 0;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(CONNECTION_PORT);
	inet_pton(AF_INET, ip, &server_address.sin_addr);
	// server_address.sin_addr.s_addr =INADDR_ANY;
	server_address.sin_zero[7] = '\0';
	status = connect(socket_descriptor, (struct sockaddr *)&server_address, sizeof(server_address));
	if (status < 0)
	{
		perror("Couldn't connect with the server");
		exit(EXIT_FAILURE);
	}

	//    pthread_create(&tid, NULL, receive_packets, &socket_descriptor);

	return socket_descriptor;
}

// int main()
// {

//     char* message="Hi";
//     char recieve_buffer[100];

//     int socket_descriptor = connect_to_server("");

//     write(socket_descriptor, message, strlen(message));

//     int s = 0;
//     while(s == 0){
//           s = read(socket_descriptor, recieve_buffer, 100);
//           printf("Message from server: %s\n", recieve_buffer);
//     }
//     close(socket_descriptor);
//     return 0;
// }
