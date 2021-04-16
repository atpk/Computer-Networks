#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <netdb.h>
#define MAXLINE 1024 

void info(struct hostent * hinfo)
{
  if(hinfo==NULL)
  {
    perror("Invalid entry!");
    exit(1);
  }
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char** argv)
{ 
    struct hostent *hinfo;
	if(argc < 2){
        printf("Enough arguments not provided.\n");
        exit (0);
    }

	int PORT = atoi(argv[1]);
	int sockfd; 
	char buff[MAXLINE]; 
    char *ipbuff;
	struct sockaddr_in serv_addr, cli_addr; 
	
	// Creating socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	    error("Socket creation error.\n");
	else 
        printf("Socket created successfully.\n");
    
	memset(&serv_addr, 0, sizeof(serv_addr)); 
	memset(&cli_addr, 0, sizeof(cli_addr)); 
	
	// Sturcture for server address
	serv_addr.sin_family = AF_INET; // IPv4 
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons(PORT); 
	
	// Bind
	if ( bind(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ){ 
		error("binding failed");
	}
	else
        printf("Binded Successfully.\n");
        
	while(1) {
        //Read data from client
		int len, n; 
		len = sizeof(cli_addr);
		n = recvfrom(sockfd, (char *)buff, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
		printf("Data received from client.\n");
        
        //Obtain IP's
		buff[n-1] = '\0'; 
		hinfo=gethostbyname(buff);
		
		//Send data to client
		int i = 0;
		while(hinfo->h_addr_list[i]) {
            ipbuff=inet_ntoa(*((struct in_addr*)hinfo->h_addr_list[i]));
	        bzero (buff, MAXLINE);
	        strcpy(buff, ipbuff);
	        sendto(sockfd, (const char *)ipbuff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, len); 
	        i++;
		}
		
		if (i > 0) {
	        bzero (buff, MAXLINE);
	        strcpy(buff, "done");
	        sendto(sockfd, (const char *)ipbuff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, len); 
		}
		else{
		    bzero (buff, MAXLINE);
	        strcpy(buff, "Error!!");
	        sendto(sockfd, (const char *)ipbuff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, len); 
		}
		
		printf("%d ip's sent for the given hostname.\n", i);
	}
	
	return 0; 
}

/*Output

Socket created successfully.
Binded Successfully.
Data received from client.
1 ip's sent for the given hostname.

*/