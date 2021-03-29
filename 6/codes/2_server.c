#include <stdio.h> 
#include <string.h>  
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> 
	
#define TRUE 1 
#define FALSE 0 
#define PORT 8888 
	
int main(int argc , char *argv[]) 
{ 
	int opt = TRUE; 
	int master_socket , addrlen , new_socket , client_socket[30] , 
		max_clients = 10 , activity, i , valread , sd; 
	int max_sd; 
	struct sockaddr_in address; 
		
	char buffer[1025]; //data buffer of 1K 
		

	fd_set readfds; 
		
	//a message 
	char *message = "You are connected to CONCURRENT server."; 
	
	//initialise all client_socket[] to 0 so not checked 
	for (i = 0; i < max_clients; i++) 
	{ 
		client_socket[i] = 0; 
	} 
		
	//create a  socket 
	if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	//set  socket to allow multiple connections , 
	//this is just a good habit, it will work without this 
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
		sizeof(opt)) < 0 ) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	printf("SERVER: socket created successfully...\n");
	// assign address here 
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
		
	//bind the socket to localhost port  
	if (bind(master_socket, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("binding error");
		exit(EXIT_FAILURE);
	}
	printf("SERVER: binded to port 8888...\n");
	
	//try to specify maximum number of pending connections for the socket and listen
	// max 10 
	if (listen(master_socket, 10) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("SERVER: started listening to clients...\n");
	
	//accept the incoming connection (Waiting for connections)
	addrlen = sizeof(address); 
		
	while(TRUE) 
	{ 
		//clear the socket set 
		FD_ZERO(&readfds);
	
		//add socket to set 
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;
		
		//add child sockets to set 
		for ( i = 0 ; i < max_clients ; i++) 
		{ 
			//socket descriptor 
			sd = client_socket[i]; 
				
			//if valid socket descriptor then add to read list 
			if(sd > 0) 
				FD_SET( sd , &readfds); 
				
			//highest file descriptor number, need it for the select function 
			if(sd > max_sd) 
				max_sd = sd; 
		} 
	
		//wait for an activity on one of the sockets , timeout is NULL , 
		//so wait indefinitely 
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL); 
	
		if ((activity < 0) && (errno!=EINTR)) 
		{ 
			printf("select error"); 
		} 
			
		//If check incoming connection using FD_ISSET
		if (FD_ISSET(master_socket, &readfds)) 
		{ 
			//accept the connection
			if ((new_socket = accept(master_socket, (struct sockaddr *) &address, (socklen_t*) &addrlen)) < 0) 
			{ 
				perror("accept"); 
				exit(EXIT_FAILURE); 
			} 
			printf("Client connected through %s : %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
					
	
	
			//send new connection greeting message 
			if (send(new_socket, message, strlen(message), 0) != strlen(message)) 
			{ 
				perror("send"); 
			} 
				
			puts("Welcome message sent successfully"); 
				
			//add new socket to array of sockets 
			for (i = 0; i < max_clients; i++) 
			{ 
				if (client_socket[i] == 0) {
					client_socket[i] = new_socket;
					printf("SERVER: Added to list of sockets...\n");
					break;
				}
			} 
		} 
			
		//else its some IO operation on some other socket 
		for (i = 0; i < max_clients; i++) 
		{ 
			sd = client_socket[i]; 
				
			//Check for FD_ISSET 
			if (FD_ISSET(sd, &readfds)) 
			{ 
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valread = read(sd, buffer, 1024)) == 0) 
				{ 
					//Somebody disconnected , get his details and print 
					getpeername(sd, (struct sockaddr *) &address, (socklen_t*) &addrlen);
					printf("Client %s : %d disconnected...\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
						
					//Close the socket and mark as 0 in list for reuse 
					close( sd ); 
					client_socket[i] = 0; 
				} 
					
				//Echo back the message that came in 
				else
				{ 
					//set the string terminating NULL byte on the end 
					//of the data read
					buffer[valread] = '\0';
					send(sd, buffer, strlen(buffer), 0);
				} 
			} 
		} 
	} 
		
	return 0; 
} 

