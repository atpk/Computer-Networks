// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
 
#define PORT 8888

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main() 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char info[1024] = {0}; 
	char buffer[1024] = {0}; 
	
	// Create socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("\n Socket creation error \n");
	printf("CLIENT: Socket created...\n");
	
	// Server address structure
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
		error("\nInvalid address/ Address not supported \n"); 

	// Connect
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	printf("CLIENT: Connected to the Server successfully....\n");
	bzero(buffer, sizeof(buffer));
	if ((read( sock , buffer, sizeof(buffer))) < 0)
		error("error on reading");
	printf("SERVER: %s\n", buffer);
	
	int aa=1;
	while(aa) {
		// Input text from user
		int b;
		printf("Enter 0 to close the connection.\n");
		scanf("%d",&b);
		if(b == 0)
			break;
		else
			continue;
	}
	
	close(sock);
	printf("CLIENT: Connection closed...\n"); 
	return 0; 
}
