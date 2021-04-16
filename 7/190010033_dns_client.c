#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#define MAXLINE 1024 

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char** argv) {

	if(argc < 3){
        printf("Enough arguments not provided.\n");
        exit (0);
    }
	
	int PORT = atoi(argv[2]);
	int sockfd; 
	char buff[MAXLINE];
	struct sockaddr_in serv_addr; 

	// Creating socket
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	    error("Socket creation error.\n");
	else
	    printf("Socket created.\n");

	memset(&serv_addr, 0, sizeof(serv_addr)); 
	
	// Structure for server address 
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); 
	
	// Input and send it to server
	int n, len;
	printf("DNS name to be entered here: ");
	fgets(buff, MAXLINE, stdin);
	sendto(sockfd, (const char *)buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)); 
	
	while (1){
	    // Read data from server
		bzero(buff, MAXLINE);
		n = recvfrom(sockfd, (char *)buff, MAXLINE, MSG_WAITALL, (struct sockaddr *) &serv_addr, &len);
		buff[n] = '\0'; 
		
		// Output
		if((strcmp(buff, "done")==0)){
			printf("Done\n");
			break;
		}
		else if((strcmp(buff, "Error!!")==0)) {
            break;
            printf("Some error occured for given hostname.\n");
		}
		else
			printf("IP Address : %s\n", buff);
	}
		
	if (close(sockfd) < 0)
	    error("Error while closing.\n");
	else
	    printf("Connection closed.\n");
	
	return 0; 
}

/*Output

Socket created.
DNS name to be entered here: google.com
IP Address : 72.14.192.0
done
Connection closed.

*/