// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
 
#define PORT 8080 

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main() 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char info[20]; 
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
	
	// Input text from user
	printf("Enter text: \n");
	scanf("%[^\n]s", buffer);
	
	// Send data to server
	if ((send(sock , buffer , strlen(buffer) , 0 )) < 0)
		error("error on writing"); 
	printf("CLIENT: Message sent to server...\n");
	
	// Read data from server
	if ((read( sock , info, sizeof(info))) < 0)
		error("error on reading"); 
	printf("CLIENT: Message received from server...\n"); 
	
	// Output
	printf("Number of characters in the given text: ");
	int i = 0;
	while (info[i] != ' ') {
		printf("%c",info[i]);
		i++;
	}
	printf("\n");
	printf("Number of words in the given text: ");
	i++;
	while (info[i] != ' ') {
		printf("%c",info[i]);
		i++;
	}
	printf("\n");
	printf("Number of sentences in the given text: ");
	i++;
	while (info[i] != '\0') {
		printf("%c",info[i]);
		i++;
	}
	printf("\n");
	
	close(sock);
	printf("CLIENT: Connection closed...\n"); 
	return 0; 
} 

