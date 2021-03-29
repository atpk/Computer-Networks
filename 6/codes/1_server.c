// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define PORT 8080 

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[]) 
{ 
	int sockfd, newsockfd; 
	struct sockaddr_in serv_addr; 
	int opt = 1; 
	int addrlen = sizeof(serv_addr); 
	char buffer[1024] = {0}; 
	char info[20]; 
	
	// Create socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
		error("socket failed");
	printf("SERVER: Socket created...\n");
	// Attack the socket to port 8080 
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
		error("setsockopt");
	
	// Server address structure
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons( PORT ); 
	
	// Binding
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) 
		error("bind failed"); 
	printf("SERVER: Socket binded successfully...\n");
	
	// Listen
	if (listen(sockfd, 3) < 0) 
		error("listen"); 
	printf("SERVER: Server started listening for client at port number: 8080 ...\n");
	
	while (1) {
		// Accept
		if ((newsockfd = accept(sockfd, (struct sockaddr *)&serv_addr, (socklen_t*)&addrlen))<0)
			error("accept");
		printf("SERVER: Accepted the connection from client...\n");
		
		// Read data from client
		if ((read( newsockfd , buffer, 1024)) < 0)
			error("error on reading");
		printf("CLIENT: %s\n",buffer );
		
		// Calculate no of chars, words, sent
		int i = 0, n_word = 0, n_sent = 0, j = 0;
		j = strlen(buffer);
		for (;i < j; i++) {
			if (buffer[i]==' ')
				n_word++;
			if (buffer[i]=='.')
				n_sent++;
		}
		n_word++;
		sprintf(info, "%d %d %d", j, n_word, n_sent);
		
		// Send data to client
		if ((send(newsockfd , info , strlen(info) , 0 )) < 0)
			error("error on writing");
		printf("SERVER: Calculated data sent\n"); 
		close(newsockfd);
		printf("SERVER: Connection closed with the client...\n");
	}
 	
 	close(sockfd);
 	printf("SERVER: Server connection closed...\n");
 	
	return 0; 
} 

